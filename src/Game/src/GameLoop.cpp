//
// Created by remy on 24-04-20.
//

#include "GameLoop.h"

std::string Gameloop::notifyEnumToMsg(notifyMessages msg) {
    switch (msg) {
        case NOT_ENOUGH_MONEY_FOR_ITEM:
            return "Not enough money to buy " + failed_to_buy_item;
        case BOUGHT_ITEM:
            return "You bought " + getInventory().getLastItemAddedAmount().str() + " " +
                   getInventory().getLastItemAdded() + "(s).";
        case MAGIC:
            return "The answer to life, the universe and everything!";
        case DEBUG:
            return "A Debug Thing Happened!";
        case NO_MSG:
        case LAST_MSG:
            return "";
    }
};

void Gameloop::cleanTerminal() {
    int lines = 80;
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
        if (cookieStepIncrement >= 1000) {
            incrementCookiesOnTime();
            cookieStepIncrement = 0;
        }
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsed = endTime - startTime;
        auto step_duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        if (step_duration < _maxFrameTimeMs) {
            std::this_thread::sleep_for(std::chrono::milliseconds(_maxFrameTimeMs - step_duration));
            cookieStepIncrement += _maxFrameTimeMs - step_duration;
        } else {
            cookieStepIncrement += step_duration;
        }
    }
}

void Gameloop::showFinalScore() {
    std::cout << "Well done. Final score: " << getWallet().getTotalcookies() << " cookies.\n";
}

void Gameloop::showInput()
{
    std::cout << "\n===== Options ====\n";
    std::cout << "c\t:\t get cookie\n";
    for (auto &item : m_Items.allItems) {
        if (getWallet().getCookieAmount() >= item.price) {
            std::cout << item.buyOneKey << "/" << item.buyMaxKey <<
                      "\t:\t buy " << item.name << " (cost 1: " <<
                      item.price << "; +" <<
                      item.cps << " cps); ";
            if (maxItemAmount(item) > 0) {
                std::cout << item.buyMaxKey << ": buy " <<
                  std::to_string(maxItemAmount(item)) <<
                  "; ";
            }
            //std::cout << "have: " << getInventory().getItemCount(item) << "\n";
            std::cout << "\n";
        }
    }
    std::cout << "q\t:\t quit\n";
    std::cout << "\nCommand + ↩:\n";
}


void Gameloop::handleChoice(const std::string &input) {
    for (Item &item : m_Items.allItems) {
        if (input == item.buyOneKey) {
            buyItem(CookieNumber(1), item);
        } else if (input == item.buyMaxKey) {
            buyItem(CookieNumber(maxItemAmount(item)), item);
        }
    }
    if (input == "c") {
        auto cmd = std::make_unique<UpdateCookiesCommand>(CookieNumber(1), getWallet());
        cmd->execute();
    }
    else if (input == "q" or input == "Q") {
        quit();
    }
    else if (input == "4") {
        getWallet().incrementCookieAmount(CookieNumber(42424242));
        setMessage(MAGIC);
    }
    else if (input == "1") {
        getWallet().incrementCookieAmount(CookieNumber(100));
        setMessage(DEBUG);
    }
    else if (input == "2") {
        getWallet().incrementCookieAmount(getWallet().getCookieAmount() * 2);
        setMessage(DEBUG);
    }
}

void Gameloop::showStatus() {
    std::cout << "\n===== Stats ====\n";
    std::cout << "Cookies\t:\t" << std::setprecision(1) <<
    getWallet().getCookieAmount() << "\n";
    std::cout << "cps\t:\t" << std::setprecision(1) <<
    getWallet().getCps() << "\n";
}

void Gameloop::incrementCookiesOnTime() {
    step_stop = std::chrono::high_resolution_clock::now();
    auto step_duration = std::chrono::duration_cast<std::chrono::seconds>(step_stop - step_start).count();
    getWallet().incrementCookieAmount(getWallet().getCps() * step_duration);
    step_start = std::chrono::high_resolution_clock::now();
}

void Gameloop::buyItem(CookieNumber amountToBuy, Item &item) {
    if(canPayForItem(amountToBuy, item)) {
        auto buyCommand = std::make_unique<BuyItemCommand>(item, amountToBuy, getInventory(), getWallet());
        buyCommand->execute();
        setMessage(BOUGHT_ITEM);
    } else {
        failed_to_buy_item = item.name;
        setMessage(NOT_ENOUGH_MONEY_FOR_ITEM);
    }
}

bool Gameloop::canPayForItem(const CookieNumber& amountToBuy, Item &item)
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

int Gameloop::maxItemAmount(Item &item) {
    if (canPayForItem(CookieNumber(500), item))
        return 500;
    if (canPayForItem(CookieNumber(250), item))
        return 250;
    if (canPayForItem(CookieNumber(100), item))
        return 100;
    if (canPayForItem(CookieNumber(50), item))
        return 50;
    if (canPayForItem(CookieNumber(10), item))
        return 10;
    return 0;
}
