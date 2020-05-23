//
// Created by remy on 24-04-20.
//

#ifndef C_OOKIECLIKER_GAMELOOP_H
#define C_OOKIECLIKER_GAMELOOP_H

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <limits>
#include <iomanip>
#include "Wallet.h"
#include "Inventory.h"
#include "BuyItemCommand.h"
#include "UpdateCpsCommand.h"
#include "UpdateCookiesCommand.h"
#include "Store.h"
#include "CookieNumbers.h"
#include <gtest/gtest_prod.h>

class Gameloop {

    std::atomic<bool> running {false};
    std::atomic<int> cookieStepIncrement {0};
    std::mutex inputMutex;
    std::mutex gameStepMutex;
    std::thread gameStepThread;
    std::thread inputThread;

    const unsigned int _maxFrameTimeMs{200}; // 0.2 sec
    //const unsigned int _maxFrameTimeMs{1000}; // 1 sec

    enum notifyMessages
    {
        NO_MSG,
        NOT_ENOUGH_MONEY_FOR_ITEM,
        BOUGHT_ITEM,
        MAGIC,
        DEBUG,
        LAST_MSG,
    };
    std::atomic<notifyMessages> notifyMessage{};
    std::string notifyEnumToMsg(notifyMessages msg);
    static void cleanTerminal();
    static std::string currentTime(const std::string& formatString = "%H:%M");
    void renderText();

    Inventory m_Inventory;
    Wallet m_Wallet;
    Store m_Store;

    std::string failed_to_buy_item;

    void showInput();
    std::chrono::high_resolution_clock::time_point step_start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point step_stop = std::chrono::high_resolution_clock::now();
    void showStatus();
    void incrementCookiesOnTime();

    void buyItem(CookieNumber amountToBuy, Item &item);
    bool canPayForItem(const CookieNumber& amountToBuy, Item &item);
    int maxItemAmount(Item &item);
    void handleChoice(const std::string &input);
    void showFinalScore();
    void setMessageTime(const std::string& timeString = "%H:%M");
    std::string lastMessageTime;
    FRIEND_TEST(GameloopTestSuite, incrementCps);

public:
    Gameloop();
    explicit Gameloop(bool isRunning);
    ~Gameloop();
    void start();
    inline void quit();
    void setMessage(notifyMessages msg);
    void input();
    void gameStep();
    Wallet &getWallet();
    Inventory &getInventory();
    Store &getStore();
};


/* ANSII escape codes for the terminal */
struct escapeCodes {
    const std::string hideCursor {"\033[?25l"};
    const std::string clearEntireScreen {"\033[2J"};
    const std::string placeCursorAt1x1 {"\033[1;1H"};
    const std::string eraseCurrentLine {"\033[A\\"};
    const std::string cursorUpOneLine {"\33[2K"};
    const std::string cursorToBeginningOfLine {"\r"};
};

/* global variable holding the escapecodes */
static const escapeCodes escapeCode;

#endif //C_OOKIECLIKER_GAMELOOP_H
