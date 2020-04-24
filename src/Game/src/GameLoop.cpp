//
// Created by remy on 24-04-20.
//

#include "GameLoop.h"

std::string Gameloop::notifyEnumToMsg(notifyMessages msg) {
    switch (msg) {
        case SCORE_DOUBLED:
            return "Bonus unlocked! Score doubled!!!";
        case THE_ANSWER:
            return "The answer to life, the universe and everything!";
        case NO_MSG:
        case LAST_MSG:
            return "";
    }
};

void Gameloop::cleanTerminal() {
    int lines = 30;
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
        std::cout << currentTime() << ": " << notifyEnumToMsg(notifyMessage);
    }
    std::cout << std::endl;
    std::cout << "Points: " << score << std::endl;
    std::cout << "Command + ↩: " << std::endl;
    std::cout << " p\t: get point " << std::endl;
    std::cout << " m\t: ??? " << std::endl;
    std::cout << " q\t: quit" << std::endl;

}

void Gameloop::updateScore() {
    if (score == 10) {
        score = score * 2;
        notifyMessage = notifyMessages::SCORE_DOUBLED;
    }
    if (score == 42)
        notifyMessage = notifyMessages::THE_ANSWER;
}

Gameloop::Gameloop() : running(true),
                       gameStepThread(&Gameloop::gameStep, this),
                       inputThread(&Gameloop::input, this), score(0), notifyMessage(NO_MSG) {
    thisGame->start();
}

Gameloop::~Gameloop() {
    inputThread.join();
    gameStepThread.join();
}

inline void Gameloop::quit() {
    running = false;
    thisGame->end();
}


void Gameloop::handleInput() {
   thisGame->handleInput();
}

void Gameloop::input() {
    while (running) {
        std::lock_guard<std::mutex> locker(inputMutex);
        handleInput();
    }
}

void Gameloop::gameStep() {
    while (running) {
        std::lock_guard<std::mutex> locker(gameStepMutex);
        auto startTime = std::chrono::high_resolution_clock::now();

        updateScore();
        cleanTerminal();
        renderText();

        // end of cycle
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsed = endTime - startTime;
        auto step_duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        if (step_duration < _maxFrameTimeMs) {
            std::this_thread::sleep_for(std::chrono::milliseconds(_maxFrameTimeMs - step_duration));
        }
    }
}
