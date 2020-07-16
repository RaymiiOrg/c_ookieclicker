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
#include "Save.h"
#include <gtest/gtest_prod.h>

class Gameloop {

    std::atomic<bool> running {false};
    std::atomic<int> cookieStepIncrement {0};
    std::mutex inputMutex;
    std::mutex gameStepMutex;
    std::mutex outputShowMutex;
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

    enum notifyMessages {
        NO_MSG,
        NOT_ENOUGH_MONEY_FOR_ITEM,
        BOUGHT_ITEM,
        MAGIC,
        DEBUG,
        SAVED,
        LOADED,
        LAST_MSG,
    };
    std::atomic<notifyMessages> notifyMessage{};
    std::string notifyEnumToMsg(notifyMessages msg);
    static void cleanTerminal();
    static std::string currentTime(const std::string& formatString = "%H:%M:%S");
    void renderText();

    Inventory m_Inventory;
    Wallet m_Wallet;
    Store m_Store;
    CookieNumberPrinter cp;
    std::string failed_to_buy_item;

    void showInput();
    void showInputBar();
    void showStoreInput(bool oneItem);
    void showInventory();
    void showAchievements();
    void showOptions();
    static std::string inputModeMapping(inputModes mode);

    std::chrono::high_resolution_clock::time_point step_start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point step_stop = std::chrono::high_resolution_clock::now();
    void showStatus();
    void incrementCookiesOnTime();

    void buyItem(CookieNumber amountToBuy, Item &item);
    bool canPayForItem(const CookieNumber& amountToBuy, Item &item);
    bool canBuyOne(Item &item);
    bool canBuyTen(Item &item);
    bool canBuyHundred(Item &item);
    int canBuyTenOrHundred(Item &item);
    int maxItemAmount(Item &item);
    void handleChoice(const std::string& input);
    void showFinalScore();
    void setMessageTime(const std::string& timeString = "%H:%M:%S");
    std::string lastMessageTime;
    std::string saveFile = ".cookieclicker.save";

    // tests
    FRIEND_TEST(GameloopTestSuite, incrementCps);
    FRIEND_TEST(GameloopTestSuite, incrementCpsLargerAmount);
    FRIEND_TEST(GameloopTestSuite, maxItemAmount);

public:
    Gameloop();
    explicit Gameloop(bool isRunning);
    ~Gameloop();
    void start();
    void reset();
    inline void quit();
    void setMessage(notifyMessages msg);
    void input();
    void gameStep();
    Wallet &getWallet();
    Inventory &getInventory();
    Store &getStore();
    void handleBuyItemChoice(const std::string &input);
};


/* ANSII escape codes for the terminal */
struct escapeCodes {
    const std::string hideCursor {"\033[?25l"};
    const std::string clearEntireScreen {"\033[2J"};
    const std::string placeCursorAt1x1 {"\033[1;1H"};
    const std::string eraseCurrentLine {"\033[A\\"};
    const std::string cursorUpOneLine {"\33[2K"};
    const std::string cursorToBeginningOfLine {"\r"};
    const std::string terminalBold {"\033[1m"};
    const std::string terminalReset {"\033[0m"};
    const std::string terminalUnderline {"\033[4m"};
    const std::string terminalDim {"\033[2m"};
};

/* global variable holding the escapecodes */
static const escapeCodes escapeCode;

#endif //C_OOKIECLIKER_GAMELOOP_H
