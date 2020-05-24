//
// Created by remy on 24-04-20.
//

#include "GameLoop.h"

std::string Gameloop::notifyEnumToMsg(notifyMessages msg) {
    switch (msg) {
        case NOT_ENOUGH_MONEY_FOR_ITEM:
            return "Not enough money to buy " + failed_to_buy_item;
        case BOUGHT_ITEM:
            return "You bought " + cp.print(getInventory().getLastItemAddedAmount()) + " " +
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
    int lines = 300;
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
        std::cout << escapeCode.terminalBold;
        std::cout << lastMessageTime << ": " << std::setprecision(15) << notifyEnumToMsg(notifyMessage);
        std::cout << escapeCode.terminalReset;
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

Gameloop::Gameloop(bool isRunning) : running(isRunning) {
}

Gameloop::~Gameloop() {
    if (inputThread.joinable())
        inputThread.join();
    if (gameStepThread.joinable())
        gameStepThread.join();
}

void Gameloop::start() {
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
    std::cout << "Well done.\n";
    std::cout << "Ended with " << cp.print(getWallet().getCookieAmount()) << " cookies.\n";
    std::cout << "Total cookies earned: " << cp.print(getWallet().getTotalcookies()) << "\n";
    std::cout << "Thank you for playing!\n";
    std::cout << "c_ookieclicker version: " << std::to_string(game::gameVersion);
    std::cout << " by Remy, https://raymii.org\n";
    if (getWallet().getCookieAmount().str().length() > 13)
        std::cout << cp.print(getWallet().getCookieAmount()) << " cookies is: " << getWallet().getCookieAmount() << "\n";
    if (getWallet().getCps().str().length() > 13)
        std::cout << cp.print(getWallet().getCps()) << " cps is: " << getWallet().getCps() << "\n";

}

void Gameloop::showInput() {
    std::cout << "\n===== Commands ====\n";
    std::cout << escapeCode.terminalBold;
    std::cout << "c\t:\t get cookie\n";
    std::cout << escapeCode.terminalReset;
    std::cout << "q\t:\t quit\n";
//    std::cout << "s\t:\t save \n";

    if (!getInventory().getInventory().empty()) {
        std::cout << "\n===== Inventory ====\n";

        for (auto &item : getInventory().getInventory()) {
            if (item.second > 0) {
                std::cout << item.first.name <<  ": " << cp.print(item.second) << "\n";
            }
        }
    }

        std::cout << "\n===== Store ====\n";
        bool enoughMoneyOrHaveItemsAlready = false;
        for (auto &item : getStore().getStoreInventory()) {
            if (!canPayForItem(1, item) && getInventory().getItemCount(item) > 0) {
                enoughMoneyOrHaveItemsAlready = true;
                std::cout << escapeCode.terminalDim;
                std::cout << item.buyOneKey << ": not enough cookies for " << item.name <<
                          " (cost: ";
                std::cout << cp.print(Store::getPrice(item));
                std::cout << " cookies);";
                std::cout << escapeCode.terminalReset << "\n";
            } else if (canPayForItem(1, item)) {
                enoughMoneyOrHaveItemsAlready = true;
                std::cout << item.buyOneKey << "/" << item.buyMaxKey <<
                ": buy " << item.name << " (cost: ";
                std::cout << cp.print(Store::getPrice(item));
                std::cout << " cookies; +";
                std::cout << cp.print(item.cps);
                std::cout << " cps); ";
                if (maxItemAmount(item) > 1) {
                    std::cout << escapeCode.terminalBold <<
                    "Max: " <<
                    "" << cp.print(maxItemAmount(item)) <<
                    escapeCode.terminalReset <<
                    "; cost: " <<
                    cp.print(Store::getPrice(item, maxItemAmount(item))) <<
                    " cookies.";
                }
                std::cout << escapeCode.terminalReset << "\n";
            }
        }
        if (!enoughMoneyOrHaveItemsAlready) {
            std::cout << "No items available, get some more cookies.\n";
        }

    std::cout << "\nCommand + ↩:\n";
}


void Gameloop::handleChoice(const std::string &input) {
    for (Item &item : getStore().getStoreInventory()) {
        if (input == item.buyOneKey) {
            buyItem(CookieNumber(1), item);
        } else if (input == item.buyMaxKey) {
            buyItem(CookieNumber(maxItemAmount(item)), item);
        }
    }
    if (input == "c") {
        auto cmd = std::make_unique<UpdateCookiesCommand>(1, getWallet());
        cmd->execute();
    } else if (input == "q" or input == "Q") {
        quit();
    } else if (input == "4") {
        getWallet().incrementCookieAmount(CookieNumber(42424242));
        setMessage(MAGIC);
    } else if (input == "1") {
        getWallet().incrementCookieAmount(CookieNumber(100));
        setMessage(DEBUG);
    } else if (input == "2") {
        getWallet().incrementCookieAmount(getWallet().getCookieAmount() * 2);
        getWallet().incrementCps(getWallet().getCps() * 2);
        setMessage(DEBUG);
    } else if (input == "3") {
        setMessage(DEBUG);
        CookieNumber a ("115119036727821003870521051126876277284277153860658940094917200695393093978299485941825124206612415512884049997084612576423130590962154289376800387194154816459487665078480150348801009011289080");
        getWallet().incrementCookieAmount(a);
        getWallet().incrementCps(a*2);
    }
}

void Gameloop::showStatus() {
    std::cout << "\n===== Stats ====\n";
    std::cout << "Cookies\t:\t";
    if (getWallet().getCookieAmount() > 0)
        std::cout << cp.print(getWallet().getCookieAmount());
    std::cout << "\n";
    std::cout << "cps\t:\t";
    if (getWallet().getCps() > 0)
        std::cout << cp.print(getWallet().getCps());
    std::cout << "\n";
}

void Gameloop::incrementCookiesOnTime() {
    step_stop = std::chrono::high_resolution_clock::now();
    auto step_duration = std::chrono::duration_cast<std::chrono::seconds>(step_stop - step_start).count();
    getWallet().incrementCookieAmount(getWallet().getCps() * step_duration);
    step_start = std::chrono::high_resolution_clock::now();
}

void Gameloop::buyItem(CookieNumber amountToBuy, Item &item) {
    if (canPayForItem(amountToBuy, item)) {
        auto buyCommand = std::make_unique<BuyItemCommand>(item, amountToBuy, getInventory(), getWallet(), getStore());
        buyCommand->execute();
        setMessage(BOUGHT_ITEM);
    } else {
        failed_to_buy_item = item.name;
        setMessage(NOT_ENOUGH_MONEY_FOR_ITEM);
    }
}

bool Gameloop::canPayForItem(const CookieNumber &amountToBuy, Item &item) {
    return getWallet().getCookieAmount() >= Store::getPrice(item, amountToBuy);
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

Store &Gameloop::getStore() {
    return m_Store;
}

CookieNumber Gameloop::maxItemAmount(Item &item) {
    if (getWallet().getCookieAmount() < (item.price * 2) - 1) {
//        std::cout << "item price equals cookies in bank" << std::endl;
        return CookieNumber(1);
    }

//    std::cout << "\n\n";
//    std::cout << "cookies in bank: " << getWallet().getCookieAmount() << std::endl;
//    std::cout << "item price: " << Store::getPrice(item) << std::endl;
    auto priceIncrease = item.percentIncreaseWhenBought;
//    std::cout << (priceIncrease / 100) << "*" <<  getWallet().getCookieAmount().convert_to<CookieFloater>() << std::endl;
    auto increaseAmount = ((priceIncrease / 100) * getWallet().getCookieAmount().convert_to<CookieFloater>());
//    std::cout << "increace percent of " << item.percentIncreaseWhenBought << " is : " << increaseAmount << " cookies" << std::endl;

    auto amountOfCookiesMinusIncreasePercentageF = getWallet().getCookieAmount().convert_to<CookieFloater>() - increaseAmount;
//    std::cout << "wallet cookies (" << getWallet().getCookieAmount() << ") - " << item.percentIncreaseWhenBought << "% (" <<
//    increaseAmount << ") = " << amountOfCookiesMinusIncreasePercentageF << std::endl;
    auto amountOfCookiesMinusIncreasePercentage = amountOfCookiesMinusIncreasePercentageF.convert_to<CookieNumber>();
//    std::cout << amountOfCookiesMinusIncreasePercentageF << " as a CookieNum is: " << amountOfCookiesMinusIncreasePercentage << std::endl;
    auto canBuy = amountOfCookiesMinusIncreasePercentage / Store::getPrice(item);
//    std::cout << "canBuy: " << canBuy << std::endl;
    if (canBuy > 1)
        return canBuy;
    else
        return (CookieNumber(1));
}

//int Gameloop::maxItemAmount(Item &item) {
//    if (canPayForItem(CookieNumber(500), item))
//        return 500;
//    if (canPayForItem(CookieNumber(250), item))
//        return 250;
//    if (canPayForItem(CookieNumber(100), item))
//        return 100;
//    if (canPayForItem(CookieNumber(50), item))
//        return 50;
//    if (canPayForItem(CookieNumber(10), item))
//        return 10;
//    return 0;
//}