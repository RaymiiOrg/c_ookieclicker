//
// Created by remy on 24-04-20.
//

#ifndef C_OOKIECLIKER_GAMELOOP_H
#define C_OOKIECLIKER_GAMELOOP_H

#include "Achievement.h"
#include "AchievementList.h"
#include "BuyItemCommand.h"
#include "CookieAmountAchievement.h"
#include "CookieNumbers.h"
#include "Inventory.h"
#include "Save.h"
#include "MainView.h"
#include "Store.h"
#include "UpdateCookiesViaInputCommand.h"
#include "UpdateCpsCommand.h"
#include "Wallet.h"
#include "notifyMessage.h"
#include "terminalCodes.h"
#include <atomic>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class Gameloop
{

    std::atomic<bool> running {false};
    std::atomic<int> cookieStepIncrement {0};
    std::mutex inputMutex;
    std::mutex gameStepMutex;
    std::thread gameStepThread;
    std::thread inputThread;

    const unsigned int _maxFrameTimeMs {200}; // 0.2 sec
    //const unsigned int _maxFrameTimeMs{500}; // 0.5 sec
    //const unsigned int _maxFrameTimeMs{1000}; // 1 sec


private:

    Wallet* wallet;
    notifyMessage* msg;
    Inventory* inventory;
    Store* store;
    MainView* gamescreen;

    std::chrono::high_resolution_clock::time_point step_start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point step_stop = std::chrono::high_resolution_clock::now();
    void incrementCookiesOnTime();

    void showFinalScore();
    void handleCookieOrQuitChoice(const std::string &input);
    void handleDebugChoice(const std::string &input);



    //FRIEND_TEST(GameloopTestSuite, incrementCps);
    //FRIEND_TEST(GameloopTestSuite, incrementCpsLargerAmount);
    //FRIEND_TEST(GameloopTestSuite, maxItemAmount);

public:
    Gameloop(notifyMessage* msg, Wallet* wallet, Inventory* inventory,
             Store* store, MainView* gamescreen);

    ~Gameloop();
    void reset();
    inline void quit();
    void input();
    void gameStep();

    void start();
};

#endif //C_OOKIECLIKER_GAMELOOP_H
