#ifndef C_OOKIECLIKER_GAMELOOP_H
#define C_OOKIECLIKER_GAMELOOP_H

#include "CookieNumbers.h"
#include "Globals.h"
#include "Inventory.h"
#include "IResettable.h"
#include "UpdateCookiesViaInputCommand.h"
#include "View.h"
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
    IResettable* itemstore;
    View* gamescreen;

    std::chrono::high_resolution_clock::time_point step_start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point step_stop = std::chrono::high_resolution_clock::now();
    std::string output;
    void incrementCookiesOnTime();

    void showFinalScore();
    void handleCookieOrQuitChoice(const std::string &input);
    void handleDebugChoice(const std::string &input);
    void processInputLine(const std::string &input);


public:
    Gameloop(notifyMessage* msg, Wallet* wallet, Inventory* inventory, IResettable* itemstore, View* gamescreen);

    ~Gameloop();
    void reset();
    void quit();
    void input();
    void gameStep();

    void start();

    void renderScreenIfOutputChanged();
};

#endif //C_OOKIECLIKER_GAMELOOP_H
