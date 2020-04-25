//
// Created by remy on 24-04-20.
//

#include "GameLoop.h"

std::string Gameloop::notifyEnumToMsg(notifyMessages msg) {
    switch (msg) {
        case NOT_ENOUGH_MONEY_FOR_ITEM:
            return "Not enough money to buy " + failed_to_buy_item;
        case BOUGHT_ITEM:
            return "You bought " + std::to_string(getInventory().getLastItemAddedAmount()) + " " +
                    getInventory().getLastItemAdded() + "(s).";
        case MAGIC:
            return "The answer to life, the universe and everything!";
        case NO_MSG:
        case LAST_MSG:
            return "";
    }
};

void Gameloop::cleanTerminal() {
    int lines = 30;
    for (int i = 0; i < lines; ++i) {
        std::cout << escapeCode.eraseCurrentLine;
        std::cout << escapeCode.cursorUpOneLine;
        std::cout << escapeCode.cursorToBeginningOfLine;
    }
}

std::string Gameloop::currentTime(const std::string &formatString) {
    auto time_point = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(time_point);
    struct tm *time_info = std::localtime(&now_c);
    std::ostringstream os;
    os << std::put_time(time_info, formatString.c_str());
    return os.str();
};

void Gameloop::renderText() {

    if (notifyMessage != NO_MSG) {
        std::cout << lastMessageTime << ": " << std::setprecision(15) << notifyEnumToMsg(notifyMessage);
    }
    std::cout << std::endl;
    showStatus();
    showInput();

}

void Gameloop::setMessage(notifyMessages msg) {
    setMessageTime(currentTime());
    notifyMessage = msg;
}

Gameloop::Gameloop() : running(true),
                       gameStepThread(&Gameloop::gameStep, this),
                       inputThread(&Gameloop::input, this), notifyMessage(NO_MSG) {
}

Gameloop::Gameloop(bool isRunning) : running(isRunning)
{
}

Gameloop::~Gameloop() {
    if (inputThread.joinable())
        inputThread.join();
    if (gameStepThread.joinable())
        gameStepThread.join();
}

void Gameloop::start()
{
    running = true;
}

inline void Gameloop::quit() {
    running = false;
    showFinalScore();
}

void Gameloop::input() {
    while (running) {
        std::lock_guard<std::mutex> locker(inputMutex);
        std::string input;
        std::getline(std::cin, input);
        handleChoice(input);
    }
}

void Gameloop::gameStep() {
    while (running) {
        std::lock_guard<std::mutex> locker(gameStepMutex);
        auto startTime = std::chrono::high_resolution_clock::now();

        cleanTerminal();
        renderText();

        // end of cycle
        incrementCookiesOnTime();
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsed = endTime - startTime;
        auto step_duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        if (step_duration < _maxFrameTimeMs) {
            std::this_thread::sleep_for(std::chrono::milliseconds(_maxFrameTimeMs - step_duration));
        }
    }
}

void Gameloop::showFinalScore() {
    std::cout << "Well done. Final score: " << std::setprecision(15) <<
    getWallet().getTotalcookies() << "\n";
}

void Gameloop::showInput()
{
    std::cout << "\n===== Options ====\n";
    std::cout << "↩\t:\t cookie\n";
    for (auto &item : m_Items.allItems) {
        if (getWallet().getCookieAmount() >= item.price)
            std::cout << item.buyOneKey << "/" << item.buyAllKey <<
                      "\t:\t buy " << item.name << " (cost: " <<
                      std::fixed << std::setprecision(0) << item.price << "; +" <<
                      std::fixed << std::setprecision(1) << item.cps << " cps; max: " <<
                      std::fixed << std::setprecision(15) <<
                      (unsigned long long) getWallet().getCookieAmount() / (unsigned long long) item.price
                      << "; have: " << getInventory().getItemCount(item) << ")\n";
    }
    std::cout << "q\t:\t quit\n";
    std::cout << "\nCommand:\n";
}


void Gameloop::handleChoice(const std::string &input) {
    for (Item &item : m_Items.allItems) {
        if (input == item.buyOneKey) {
            buyItem(1, item);
        } else if (input == item.buyAllKey) {
            buyItem(getWallet().getCookieAmount() / item.price, item);
        }
    }
    if (input.empty()) {
        auto cmd = std::make_unique<UpdateCookiesCommand>(1, getWallet());
        cmd->execute();
    }
    else if (input == "4") {
        getWallet().incrementCookieAmount(4242424242);
        setMessage(MAGIC);
    }
    else if (input == "1") {
        getWallet().incrementCookieAmount(100);
    }
    else if (input == "q" or input == "Q") {
        quit();
    }
}

void Gameloop::showStatus() {
    std::cout << "\n===== Stats ====\n";
    std::cout << "Cookies\t:\t" <<
    std::setprecision(std::numeric_limits<unsigned long long>::max_digits10) <<
    getWallet().getCookieAmount() << "\n";
    std::cout << "cps\t:\t";
    if (getWallet().getCps() < 10)
        std::cout << std::setprecision(1);
    else
        std::cout << std::setprecision(0);
    std::cout << std::fixed << getWallet().getCps() << "\n";
}

void Gameloop::incrementCookiesOnTime() {
    step_stop = std::chrono::high_resolution_clock::now();
    auto step_duration = std::chrono::duration_cast<std::chrono::milliseconds>(step_stop - step_start).count();
    getWallet().incrementCookieAmount((getWallet().getCps() / 1000) * step_duration);
    step_start = std::chrono::high_resolution_clock::now();
}

void Gameloop::buyItem(int amountToBuy, Item &item) {
    if(canPayForItem(amountToBuy, item)) {
        auto buyCommand = std::make_unique<BuyItemCommand>(item, amountToBuy, getInventory(), getWallet());
        buyCommand->execute();
        setMessage(BOUGHT_ITEM);
    } else {
        failed_to_buy_item = item.name;
        setMessage(NOT_ENOUGH_MONEY_FOR_ITEM);
    }
}

bool Gameloop::canPayForItem(int amountToBuy, Item &item)
{
    return getWallet().getCookieAmount() >= (amountToBuy * item.price);
}

void Gameloop::setMessageTime(const std::string &timeString) {
    lastMessageTime = timeString;
}

Inventory &Gameloop::getInventory() {
    return m_Inventory;
}

Wallet &Gameloop::getWallet() {
    return m_Wallet;
}
