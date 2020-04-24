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
#include <iomanip>
#include "Game.h"

class Gameloop {

    std::unique_ptr<Game> thisGame = std::make_unique<Game>();

    std::atomic<bool> running;
    std::atomic<int> score;

    std::mutex inputMutex;
    std::mutex gameStepMutex;

    std::thread gameStepThread;
    std::thread inputThread;

    const unsigned int _maxFrameTimeMs{25};

    enum notifyMessages
    {
        NO_MSG,
        SCORE_DOUBLED,
        THE_ANSWER,
        LAST_MSG,
    };
    std::atomic<notifyMessages> notifyMessage;

    static std::string notifyEnumToMsg(notifyMessages msg);
    void cleanTerminal();
    static std::string currentTime(const std::string& formatString = "%H:%M");
    void renderText();
    void updateScore();

public:
    Gameloop();
    ~Gameloop();
    inline void quit();
    void handleInput();
    void input();
    void gameStep();

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
