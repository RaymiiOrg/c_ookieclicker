//
// Created by remy on 24-04-20.
//

#include "GameLoop.h"
#include "filesystem.h"

Gameloop::Gameloop() :
    running(true),
    gameStepThread(&Gameloop::gameStep, this),
    inputThread(&Gameloop::input, this)
{
    gamescreen = std::make_unique<Screen>(&m_Wallet, &currentMessage, &m_Inventory, &m_Store);
}
Gameloop::Gameloop(bool isRunning) :
    running(isRunning)
{
}

Gameloop::~Gameloop()
{
    if (inputThread.joinable())
        inputThread.join();
    if (gameStepThread.joinable())
        gameStepThread.join();
}

inline void Gameloop::quit()
{
    running = false;
    showFinalScore();
}

void Gameloop::input()
{
    while (running)
    {
        //showInput();
        std::lock_guard<std::mutex> locker(inputMutex);
        std::string input;
        std::getline(std::cin, input);
        for (char &c : input)
        {
            std::string choice(1, c);
            handleChoice(choice);
            if (gamescreen != nullptr)
                gamescreen->handleInput(choice);
        }
    }
}

void Gameloop::gameStep()
{
    while (running)
    {
        std::lock_guard<std::mutex> locker(gameStepMutex);
        auto startTime = std::chrono::high_resolution_clock::now();
        if (gamescreen != nullptr)
        {
            gamescreen->render();
        }
        else
        {
            std::cout << "Loading screens..." << std::endl;
        }

        // end of cycle
        if (cookieStepIncrement >= 1000)
        { //(1 second)
            incrementCookiesOnTime();
            cookieStepIncrement = 0;
        }
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsed = endTime - startTime;
        auto step_duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        if (step_duration < _maxFrameTimeMs)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(_maxFrameTimeMs - step_duration));
            cookieStepIncrement += _maxFrameTimeMs - step_duration;
        }
        else
        {
            cookieStepIncrement += step_duration;
        }
    }
}

void Gameloop::showFinalScore()
{
    std::cout << escapeCode.clearEntireScreen << escapeCode.cursorTo0x0;
    std::cout << "Well done.\n";
    std::cout << "Ended with " << cp.print(getWallet().getCookieAmount()) << " cookies.\n";
    std::cout << "Total cookies earned: " << cp.print(getWallet().getTotalcookies()) << "\n";
    std::cout << "Thank you for playing!\n";
    std::cout << "c_ookieclicker version: " << std::to_string(game::gameVersion);
    std::cout << " by Remy, https://raymii.org\n";
}

void Gameloop::showInput()
{
    //
    //
    //    switch (inputMode) {
    //        case FIRST_MODE:
    //        case ONE_ITEM:
    //            showStoreInput(true);
    //            break;
    //        case ALL_ITEMS:
    //            showStoreInput(false);
    //            break;
    //        case INVENTORY:
    //            showInventory();
    //            break;
    //        case ACHIEVEMENTS:
    //            showAchievements();
    //            break;
    //        case OPTIONS:
    //            //showOptions();
    //            break;
    //        default:
    //            break;
    //    }
}

void Gameloop::showStoreInput(bool oneItem)
{
    std::cout << "\n===== Store ====\n";
    bool enoughMoneyOrHaveItemsAlready = false;
    for (auto &item : getStore().getStoreInventory())
    {
        auto itemCount = getInventory().getItemCount(item.name);
        if (!canPayForItem(1, item) && itemCount > 0)
        {
            enoughMoneyOrHaveItemsAlready = true;
            std::cout << escapeCode.terminalDim;
            std::cout << "[" << item.buyOneCursor << "]: not enough cookies for " << item.name << " (cost: ";
            std::cout << cp.print(Store::getPrice(item, itemCount));
            std::cout << " cookies);";
            std::cout << escapeCode.terminalReset << "\n";
        }
        else if (canPayForItem(1, item))
        {
            enoughMoneyOrHaveItemsAlready = true;
            if (oneItem)
            {
                std::cout << "[" << item.buyOneCursor << "]"
                          << ": buy " << item.name << "; cost: ";
                std::cout << cp.print(Store::getPrice(item, itemCount));
                std::cout << " cookies; +";
                std::cout << cp.print(item.cps);
                std::cout << " cps; ";
            }
            else
            {
                int maxbuy = canBuyTenOrHundred(item);
                if (maxbuy == 10)
                {
                    CookieNumber cpsOfTen = item.cps * CookieNumber(maxbuy);
                    std::cout << "[" << item.buyMaxCursor << "]"
                              << ": buy 10 " << item.name << "s; cost: " << cp.print(Store::getPriceOfTen(item, itemCount)) << " cookies; +" << cp.print(cpsOfTen) << " cps; ";
                }
                else if (maxbuy == 100)
                {
                    CookieNumber cpsOfHundred = item.cps * CookieNumber(maxbuy);
                    std::cout << "[" << item.buyMaxCursor << "]"
                              << ": buy 100 " << item.name << "s; cost: " << cp.print(Store::getPriceOfHundred(item, itemCount)) << " cookies +" << cp.print(cpsOfHundred) << " cps; ";
                }
                else
                {
                    std::cout << escapeCode.terminalDim;
                    std::cout << "[" << item.buyMaxCursor << "]: not enough cookies for 10 " << item.name << "s (cost: ";
                    std::cout << cp.print(Store::getPriceOfTen(item, itemCount));
                    std::cout << " cookies);";
                    std::cout << escapeCode.terminalReset;
                }
            }
            std::cout << escapeCode.terminalReset << "\n";
        }
    }
    if (!enoughMoneyOrHaveItemsAlready)
    {
        std::cout << "No items available, get some more cookies.\n";
    }
}

void Gameloop::handleChoice(const std::string &input)
{

    handleGenericChoice(input);
    //handleInputSwitchChoice(input);

//    switch (inputMode) {
//        case FIRST_MODE:
//        case ONE_ITEM:
//            handleBuyItemChoice(input);
//            break;
//        case ALL_ITEMS:
//        case INVENTORY:
//        case ACHIEVEMENTS:
//            handleAchievementViewChoice(input);
//        case OPTIONS:
//        default:
//            break;
//    }
#ifndef NDEBUG
    handleDebugChoice(input);
#endif
}

void Gameloop::handleBuyItemChoice(const std::string &input)
{
    for (Item &item : getStore().getStoreInventory())
    {
        if (input == item.buyOneCursor && canPayForItem(1, item))
        {
            buyItem(CookieNumber(1), item);
        }
        else if (input == item.buyMaxCursor)
        {
            int maxbuy = canBuyTenOrHundred(item);
            if ((maxbuy == 10 && canPayForItem(10, item)) or (maxbuy == 100 && canPayForItem(100, item)))
            {
                buyItem(CookieNumber(maxbuy), item);
            }
            else
            {
                currentMessage.setLastItemFailedToBuy(item.name);
                currentMessage.setCurrentMessage(notifyMessage::msgType::NOT_ENOUGH_MONEY_FOR_ITEM);
            }
        }
    }
}

void Gameloop::incrementCookiesOnTime()
{
    step_stop = std::chrono::high_resolution_clock::now();
    auto step_duration = std::chrono::duration_cast<std::chrono::seconds>(step_stop - step_start).count();
    getWallet().incrementCookieAmount(getWallet().getCps() * step_duration);
    step_start = std::chrono::high_resolution_clock::now();
}

void Gameloop::buyItem(const CookieNumber &amountToBuy, Item &item)
{
    if (canPayForItem(amountToBuy, item) && amountToBuy > CookieNumber(0))
    {
        auto buyCommand = std::make_unique<BuyItemCommand>(item, amountToBuy, getInventory(), getWallet(), getStore());
        buyCommand->execute();
        currentMessage.setLastItemBoughtName(item.name);
        currentMessage.setLastItemBoughtAmount(amountToBuy);
        currentMessage.setCurrentMessage(notifyMessage::msgType::BOUGHT_ITEM);
    }
    else
    {
        currentMessage.setLastItemFailedToBuy(item.name);
        currentMessage.setCurrentMessage(notifyMessage::msgType::NOT_ENOUGH_MONEY_FOR_ITEM);
    }
}

bool Gameloop::canPayForItem(const CookieNumber &amountToBuy, Item &item)
{
    if (amountToBuy == CookieNumber(100) && canBuyHundred(item))
        return true;
    if (amountToBuy == CookieNumber(10) && canBuyTen(item))
        return true;

    return canBuyOne(item);
}

Inventory &Gameloop::getInventory()
{
    return m_Inventory;
}

Wallet &Gameloop::getWallet()
{
    return m_Wallet;
}

Store &Gameloop::getStore()
{
    return m_Store;
}

bool Gameloop::canBuyOne(Item &item)
{
    auto itemCount = getInventory().getItemCount(item.name);
    return getWallet().getCookieAmount() >= Store::getPrice(item, itemCount);
}

bool Gameloop::canBuyTen(Item &item)
{
    if (!canBuyOne(item))
        return false;
    auto itemCount = getInventory().getItemCount(item.name);
    if (Store::getPriceOfTen(item, itemCount) > getWallet().getCookieAmount())
        return false;
    return true;
}

bool Gameloop::canBuyHundred(Item &item)
{
    if (!canBuyTen(item))
        return false;
    auto itemCount = getInventory().getItemCount(item.name);
    if (Store::getPriceOfHundred(item, itemCount) > getWallet().getCookieAmount())
        return false;
    return true;
}

int Gameloop::canBuyTenOrHundred(Item &item)
{
    int maxbuy = 0;
    if (canBuyTen(item))
    {
        maxbuy = 10;
        if (canBuyHundred(item))
        {
            maxbuy = 100;
        }
    }
    return maxbuy;
}

int Gameloop::maxItemAmount(Item &item)
{
    CookieNumber priceOfX;
    for (int i = 0; i < 101; ++i)
    {
        priceOfX += Store::getPrice(item, getInventory().getItemCount(item.name) + i);
        if (priceOfX > getWallet().getCookieAmount())
            return i;
    }
    return 0;
}
//
//std::string Gameloop::inputModeMapping(Gameloop::inputModes mode) {
//    switch (mode) {
//        case ONE_ITEM:
//            return "[1]: Buildings | ";
//        case ALL_ITEMS:
//            return "[2]: Buildings (10/100) | ";
//        case INVENTORY:
//            return "[3]: Inventory | ";
//        case ACHIEVEMENTS:
//            return "[4]: Achievements | ";
//        case OPTIONS:
//            return "[5]: Options";
//        default:
//            return "";
//    }
//}

void Gameloop::reset()
{
    getWallet().reset();
    getInventory().reset();
    getStore().reset();
}

void Gameloop::handleGenericChoice(const std::string &input)
{
    if (input == "c")
    {
        auto cmd = std::make_unique<UpdateCookiesCommand>(getInventory().getCookiesPerTap(), getWallet());
        cmd->execute();
    }
    else if (input == "q")
    {
        quit();
    }
}

//void Gameloop::handleSaveLoadChoice(const std::string &input) {
//
//}
//
//void Gameloop::handleInputSwitchChoice(const std::string &input) {
//    if (input == "1" or input == "2" or input == "3" or input == "4" or input == "5") {
//        inputMode = static_cast<inputModes>(std::stoi(input));
//    }
//}

void Gameloop::handleDebugChoice(const std::string &input)
{
    if (input == "7")
    {
        getWallet().incrementCookieAmount(CookieNumber(100));
        currentMessage.setCurrentMessage(notifyMessage::msgType::DEBUG);
    }
    else if (input == "8")
    {
        getWallet().incrementCookieAmount(getWallet().getCookieAmount() * 2);
        getWallet().incrementCps(getWallet().getCps() * 2);
        currentMessage.setCurrentMessage(notifyMessage::msgType::DEBUG);
    }
    else if (input == "9")
    {
        currentMessage.setCurrentMessage(notifyMessage::msgType::DEBUG);
        CookieNumber a(
            "115119036727821003870521051999708461"
            "257642313059096215428937680038718894154"
            "816459487665078480150348801009011289080");
        getWallet().incrementCookieAmount(a);
        getWallet().incrementCps(a * 2);
    }
}
