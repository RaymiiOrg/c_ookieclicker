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
        case SAVED:
            return "Game saved.";
        case LOADED:
            return "Loaded saved game from file";
        case NO_MSG:
        case LAST_MSG:
        default:
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
        std::cout << lastMessageTime << ": " << notifyEnumToMsg(notifyMessage);
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
    std::cout << std::endl;
    std::cout << escapeCode.terminalBold;
    if (getInventory().getCookiesPerTap() == CookieNumber(1))
        std::cout << "[c]\t:\t get cookie\n";
    else if (getInventory().getCookiesPerTap() > CookieNumber(1))
        std::cout << "[c]\t:\t get " << getInventory().getCookiesPerTap() << " cookies\n";
    std::cout << escapeCode.terminalReset;

    showInputBar();

    switch (inputMode) {
        case FIRST_MODE:
        case ONE_ITEM:
            showStoreInput(true);
            break;
        case ALL_ITEMS:
            showStoreInput(false);
            break;
        case INVENTORY:
            showInventory();
            break;
        case ACHIEVEMENTS:
            showAchievements();
            break;
        case OPTIONS:
            showOptions();
            break;
        default:
            break;
    }

    std::cout << "\nCommand + ↩:\n";
}

void Gameloop::showInventory() {
    if (!getInventory().getInventory().empty()) {
        std::cout << "\n===== Inventory ====\n";

        for (auto &item : getInventory().getInventory()) {
            if (item.second > 0) {
                std::cout << item.first <<  ": " << cp.print(item.second) << "\n";
            }
        }
    }
}

void Gameloop::showOptions() {
    std::cout << "\n===== Options ====\n";

    std::cout << "[q]: quit; \n";
    std::cout << "[s]: save; \n";
    std::cout << "[l]: load; \n";
    std::cout << std::endl;
    std::cout << "version: " << game::gameVersion << std::endl;
}

void Gameloop::showInputBar() {
    std::cout << std::endl;
    for (int i = static_cast<int>(inputModes::FIRST_MODE); i < static_cast<int>(inputModes::LAST_MODE); ++i) {
        if (inputMode == static_cast<inputModes>(i)) {
            std::cout << escapeCode.terminalBold <<
            inputModeMapping(static_cast<inputModes>(i)) <<
            escapeCode.terminalReset;
        } else {
            std::cout << inputModeMapping(static_cast<inputModes>(i));
        }
    }
    std::cout << std::endl;
}

void Gameloop::showStoreInput(bool oneItem) {
    std::cout << "\n===== Store ====\n";
    bool enoughMoneyOrHaveItemsAlready = false;
    for (auto &item : getStore().getStoreInventory()) {
        auto itemCount = getInventory().getItemCount(item.name);
        if (!canPayForItem(1, item) && itemCount > 0) {
            enoughMoneyOrHaveItemsAlready = true;
            std::cout << escapeCode.terminalDim;
            std::cout << "[" << item.buyOneKey << "]: not enough cookies for " << item.name <<
                      " (cost: ";
            std::cout << cp.print(Store::getPrice(item, itemCount));
            std::cout << " cookies);";
            std::cout << escapeCode.terminalReset << "\n";
        } else if (canPayForItem(1, item)) {
            enoughMoneyOrHaveItemsAlready = true;
            if (oneItem) {
                std::cout << "[" << item.buyOneKey << "]" <<
                          ": buy " << item.name << "; cost: ";
                std::cout << cp.print(Store::getPrice(item, itemCount));
                std::cout << " cookies; +";
                std::cout << cp.print(item.cps);
                std::cout << " cps; ";
            } else {
                int maxbuy = tenOrHundred(item);
                if (maxbuy == 10) {
                    std::cout << "[" << item.buyMaxKey << "]" <<
                              ": buy 10 " << item.name << "s; cost: " <<
                              cp.print(Store::getPriceOfTen(item, itemCount)) <<
                              " cookies;";
                } else if (maxbuy == 100) {
                    std::cout << "[" << item.buyMaxKey << "]" <<
                              ": buy 100 " << item.name << "s; cost: " <<
                              cp.print(Store::getPriceOfHundred(item, itemCount)) <<
                              " cookies;";
                } else {
                    std::cout << escapeCode.terminalDim;
                    std::cout << "[" << item.buyMaxKey << "]: not enough cookies for 10 " << item.name <<
                              "s (cost: ";
                    std::cout << cp.print(Store::getPriceOfTen(item, itemCount));
                    std::cout << " cookies);";
                    std::cout << escapeCode.terminalReset;
                }
            }
            std::cout << escapeCode.terminalReset << "\n";
        }
    }
    if (!enoughMoneyOrHaveItemsAlready) {
        std::cout << "No items available, get some more cookies.\n";
    }
}


void Gameloop::handleChoice(const std::string& input) {
    for (Item &item : getStore().getStoreInventory()) {
        if (input == item.buyOneKey) {
            buyItem(CookieNumber(1), item);
        } else if (input == item.buyMaxKey) {
            int maxbuy = tenOrHundred(item);
            if (maxbuy == 10 or maxbuy == 100) {
                buyItem(CookieNumber(maxbuy), item);
            } else {
                failed_to_buy_item = item.name;
                setMessage(NOT_ENOUGH_MONEY_FOR_ITEM);
            }
        }
    }
    if (input == "c") {
        auto cmd = std::make_unique<UpdateCookiesCommand>(getInventory().getCookiesPerTap(), getWallet());
        cmd->execute();
    } else if (input == "q") {
        quit();
    } else if (input == "s") {
        auto saveGame = Save(saveFile, getInventory(), getWallet(), getStore(), 1);
        if (saveGame.save()) {
            setMessage(SAVED);
        }
    } else if (input == "l") {
        auto saveGame = Save(saveFile, getInventory(), getWallet(), getStore(), 1);
        if (saveGame.load()) {
            setMessage(LOADED);
        }
    } else if (input == "1" or input == "2" or input == "3" or input == "4" or input == "5") {
        inputMode = static_cast<inputModes>(std::stoi(input));
    } else if (input == "42") {
        getWallet().incrementCookieAmount(CookieNumber(42));
        setMessage(MAGIC);
    } else if (input == "7") {
        getWallet().incrementCookieAmount(CookieNumber(100));
        setMessage(DEBUG);
    } else if (input == "8") {
        getWallet().incrementCookieAmount(getWallet().getCookieAmount() * 2);
        getWallet().incrementCps(getWallet().getCps() * 2);
        setMessage(DEBUG);
    } else if (input == "9") {
        setMessage(DEBUG);
        CookieNumber a ("1151190367278210038705210519997084612576423130590962154289376800387194154816459487665078480150348801009011289080");
        getWallet().incrementCookieAmount(a);
        getWallet().incrementCps(a*2);
    }
}

void Gameloop::showStatus() {
    std::cout << "\n===== c_ookieclicker by Remy ====\n";
    std::cout << "Cookies\t:\t";
    if (getWallet().getCookieAmount() > 0)
        std::cout << cp.print(getWallet().getCookieAmount());
    std::cout << "\n";
    std::cout << "cps\t:\t";
    if (getWallet().getCps() > 0)
        std::cout << cp.print(getWallet().getCps());
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
    if (amountToBuy == CookieNumber(10) && canBuyTen(item))
        return true;
    if (amountToBuy == CookieNumber(100) && canBuyHundred(item))
        return true;

    return getWallet().getCookieAmount() >= Store::getPrice(item, getInventory().getItemCount(item.name));
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


bool Gameloop::canBuyTen(Item &item) {
    auto itemCount = getInventory().getItemCount(item.name);
    if (Store::getPriceOfTen(item, itemCount) > getWallet().getCookieAmount())
        return false;
    return true;
}

bool Gameloop::canBuyHundred(Item &item) {
    if (!canBuyTen(item))
        return false;
    auto itemCount = getInventory().getItemCount(item.name);
    if (Store::getPriceOfHundred(item, itemCount) > getWallet().getCookieAmount())
        return false;
    return true;
}

int Gameloop::tenOrHundred(Item &item) {
    int maxbuy = 0;
    if (canBuyTen(item)) {
        maxbuy = 10;
        if (canBuyHundred(item)) {
            maxbuy = 100;
        }
    }
    return maxbuy;
}

int Gameloop::maxItemAmount(Item &item) {
    CookieNumber priceOfX;
    for (int i = 0; i < 101; ++i) {
        priceOfX += Store::getPrice(item, getInventory().getItemCount(item.name) + i);
        if (priceOfX > getWallet().getCookieAmount())
            return i;
    }
}

std::string Gameloop::inputModeMapping(Gameloop::inputModes mode) {
    switch (mode) {
        case ONE_ITEM:
            return "[1]: Store | ";
        case ALL_ITEMS:
            return "[2]: Store Max | ";
        case INVENTORY:
            return "[3]: Inventory | ";
        case ACHIEVEMENTS:
            return "[4]: Achievements | ";
        case OPTIONS:
            return "[5]: Options";
        default:
            return "";
    }
}

void Gameloop::reset() {
    getWallet().reset();
    getInventory().reset();
    getStore().reset();
}
