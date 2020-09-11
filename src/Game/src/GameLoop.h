//
// Created by remy on 24-04-20.
//

#ifndef C_OOKIECLIKER_GAMELOOP_H
#define C_OOKIECLIKER_GAMELOOP_H

#include "Wallet.h"
#include "Inventory.h"
#include "BuyItemCommand.h"
#include "UpdateCpsCommand.h"
#include "UpdateCookiesCommand.h"
#include "CookieAmountAchievement.h"
#include "AchievementList.h"
#include "notifyMessage.h"
#include "Achievement.h"
#include "Store.h"
#include "CookieNumbers.h"
#include "Save.h"
#include "Screen.h"
#include "terminalCodes.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <limits>
#include <iomanip>
#include <gtest/gtest_prod.h>

class Gameloop {

    std::atomic<bool> running {false};
    std::atomic<int> cookieStepIncrement {0};
    std::mutex inputMutex;
    std::mutex gameStepMutex;
    std::thread gameStepThread;
    std::thread inputThread;

    const unsigned int _maxFrameTimeMs{200}; // 0.2 sec
    //const unsigned int _maxFrameTimeMs{500}; // 0.5 sec
    //const unsigned int _maxFrameTimeMs{1000}; // 1 sec

    enum inputModes {
        FIRST_MODE,
        ONE_ITEM,
        ALL_ITEMS,
        INVENTORY,
        ACHIEVEMENTS,
        OPTIONS,
        LAST_MODE,
    };
    std::atomic<inputModes> inputMode = ONE_ITEM;

    enum achievementViews {
        COOKIE_AMOUNT,
        COOKIES_PER_SECOND,
    };
    std::atomic<achievementViews> achievementView = COOKIE_AMOUNT;


private:
    Inventory m_Inventory;
    Wallet m_Wallet;
    Store m_Store;

    void showInput();
    void showInputBar();
    void showStoreInput(bool oneItem);
    void showInventory();
    void showAchievements();
    notifyMessage currentMessage;
    static std::string inputModeMapping(inputModes mode);

    std::chrono::high_resolution_clock::time_point step_start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point step_stop = std::chrono::high_resolution_clock::now();
    void incrementCookiesOnTime();

    void buyItem(const CookieNumber& amountToBuy, Item &item);
    bool canPayForItem(const CookieNumber& amountToBuy, Item &item);
    bool canBuyOne(Item &item);
    bool canBuyTen(Item &item);
    bool canBuyHundred(Item &item);
    int canBuyTenOrHundred(Item &item);
    int maxItemAmount(Item &item);
    void handleChoice(const std::string& input);
    void showFinalScore();



    std::shared_ptr<AchievementList<CookieAmountAchievement>> cookieAmountAchievements =
            std::make_shared<AchievementList<CookieAmountAchievement>>(std::vector<std::shared_ptr<CookieAmountAchievement>>());

    void loadCookieAmountAchievements();
    void handleBuyItemChoice(const std::string &input);
    void handleGenericChoice(const std::string &input);
    void handleSaveLoadChoice(const std::string &input);
    void handleInputSwitchChoice(const std::string &input);
    void handleAchievementViewChoice(const std::string &input);
    void handleDebugChoice(const std::string& input);

    std::unique_ptr<Screen> gamescreen;

    struct achievementViewMapping {
        achievementViews view;
        std::string inputKey;
        std::string description;
    };

    std::vector<achievementViewMapping> achievementviewmap {
            {COOKIE_AMOUNT, "a", "Cookie Amount"},
            {COOKIES_PER_SECOND, "b", "Cookies per Second"},
    };

    template <typename T>
    void showAchievement(const T& achievementList) {
        for (const auto &a : achievementList->getAchievements()) {
            if (a != nullptr && a->hasAchieved()) {
                std::cout << a->name() << ": " << a->description() << std::endl;
            }
        }
    }

    FRIEND_TEST(GameloopTestSuite, incrementCps);
    FRIEND_TEST(GameloopTestSuite, incrementCpsLargerAmount);
    FRIEND_TEST(GameloopTestSuite, maxItemAmount);

public:
    Gameloop();
    explicit Gameloop(bool isRunning);
    ~Gameloop();
    void reset();
    inline void quit();
    void input();
    void gameStep();
    Wallet &getWallet();
    Inventory &getInventory();
    Store &getStore();
};



#endif //C_OOKIECLIKER_GAMELOOP_H
