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
    long double getCookieAmount() const;
    long double getCps() const;

private:
    bool finished {false};
    long double cps {0};
    long double cookieAmount {120};
    long long totalcookies {static_cast<long long>(cookieAmount)};
    unsigned long long stepcount {0};
    void update();
    void render();
    void incrementCps(long double amount);
    void incrementCookieAmount(long double amount = 1);
    void showInput() const;
    std::chrono::high_resolution_clock::time_point step_start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point step_stop = std::chrono::high_resolution_clock::now();
    void showInventory() const;
    void handleInput();
    void incrementCookiesOnTime();
    void buyCursor(int amount);
};


#endif //C_OOKIECLIKER_GAME_H
