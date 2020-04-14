//
// Created by remy on 14-04-20.
//

#ifndef C_OOKIECLIKER_GAME_H
#define C_OOKIECLIKER_GAME_H
#include <iostream>
#include <string>
#include <chrono>

class Game
{
public:
    void start();
    void end();
    void next_iteration();
    bool isFinished() const;
    double getCookieAmount() const;
    double getCps() const;

private:
    bool finished {false};
    double cps {0};
    double cookieAmount {120};
    unsigned long long stepcount {0};
    void update();
    void render();
    void incrementCps(double amount);
    void incrementCookieAmount(double amount = 1);
    void showInput() const;
    std::chrono::high_resolution_clock::time_point step_start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point step_stop = std::chrono::high_resolution_clock::now();
    void showInventory() const;
    void handleInput();
    void incrementCookiesOnTime();
    void buyCursor();
};


#endif //C_OOKIECLIKER_GAME_H
