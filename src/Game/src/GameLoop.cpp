//
// Created by remy on 24-04-20.
//

#include "GameLoop.h"

std::string Gameloop::notifyEnumToMsg(notifyMessages msg) {
    switch (msg) {
        case NOT_ENOUGH_MONEY_FOR_ITEM:
            return "Not enough money to buy " + failed_to_buy_item;
        case BOUGHT_ITEM:
            return "You bought " + std::to_string(m_Inventory->getLastItemAddedAmount()) + " " +
                    m_Inventory->getLastItemAdded() + ".";
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
        std::cout << lastMessageTime << ": " << notifyEnumToMsg(notifyMessage);
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
    std::cout << "Well done. Final score: " << m_Wallet->getTotalcookies() << "\n";
}

void Gameloop::showInput() const
{
    std::cout << "\n===== Options ====\n";
    std::cout << "↩\t:\t cookie\n";
    for (auto &item : m_Items.allItems) {
        if (m_Wallet->getCookieAmount() >= item.price)
            std::cout << item.buyOneKey << "/" << item.buyAllKey <<
                      "\t:\t buy " << item.name << "(cost: " <<
                      std::fixed << std::setprecision(0) << item.price << "; +" <<
                      std::fixed << std::setprecision(1) << item.cps << " cps; max: " <<
                      std::fixed << std::setprecision(0) <<
                      (int) m_Wallet->getCookieAmount() / (int) item.price
                      << "). Have: " << m_Inventory->getItemCount(item) << ".\n";
    }
    std::cout << "q\t:\t quit\n";
    std::cout << "\nCommand:\n";
}


void Gameloop::handleChoice(const std::string &input) {
    for (Item &item : m_Items.allItems) {
        if (input == item.buyOneKey) {
            buyItem(1, item);
        } else if (input == item.buyAllKey) {
            buyItem(static_cast<long long>(m_Wallet->getCookieAmount() / item.price),
                    item);
        }
    }
    if (input.empty()) {
        auto cmd = std::make_unique<UpdateCookiesCommand>(1, *m_Wallet);
        cmd->execute();
    }
    else if (input == "4") {
        m_Wallet->incrementCookieAmount(424242);
        setMessage(MAGIC);
    }
    else if (input == "q" or input == "Q") {
        quit();
    }
}

void Gameloop::showStatus() const {
    std::cout << "\n===== Stats ====\n";
    std::cout << "Cookies\t:\t" << static_cast<int>(m_Wallet->getCookieAmount()) << "\n";
    std::cout << "cps\t:\t" << std::setprecision(1) << std::fixed << m_Wallet->getCps() << "\n";
}

void Gameloop::incrementCookiesOnTime() {
    step_stop = std::chrono::high_resolution_clock::now();
    auto step_duration = std::chrono::duration_cast<std::chrono::milliseconds>(step_stop - step_start).count();
    m_Wallet->incrementCookieAmount((m_Wallet->getCps()/1000) * step_duration);
    step_start = std::chrono::high_resolution_clock::now();
}

void Gameloop::buyItem(int amountToBuy, Item &item) {
    if(canPayForItem(amountToBuy, item)) {
        auto buyCommand = std::make_unique<BuyItemCommand>(item, amountToBuy, *m_Inventory, *m_Wallet);
        buyCommand->execute();
        setMessage(BOUGHT_ITEM);
    } else {
        failed_to_buy_item = item.name;
        setMessage(NOT_ENOUGH_MONEY_FOR_ITEM);
    }
}

bool Gameloop::canPayForItem(int amountToBuy, Item &item) const
{
    return m_Wallet->getCookieAmount() >= (amountToBuy * item.price);
}

void Gameloop::setMessageTime(const std::string &timeString) {
    lastMessageTime = timeString;
}

Wallet &Gameloop::getWallet() const {
    return *m_Wallet;
}
