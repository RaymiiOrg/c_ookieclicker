//
// Created by remy on 14-04-20.
//

#ifndef C_OOKIECLIKER_GAME_H
#define C_OOKIECLIKER_GAME_H

#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <chrono>
#include "Item.h"
#include "Inventory.h"
#include "BuyItemCommand.h"
#include "UpdateCookiesCommand.h"
#include "UpdateCpsCommand.h"
#include "Wallet.h"

class Game
{
public:
    void start();
    void end();
    void next_iteration();
    bool isFinished() const;
    void endTurn();
    friend class Gameloop;

private:
    std::unique_ptr<Inventory> m_Inventory = std::make_unique<Inventory>();
    std::unique_ptr<Wallet> m_Wallet = std::make_unique<Wallet>();
    Items m_Items;
    bool finished {false};
    unsigned long long stepcount {0};
    void update();
    void render();
    static void clearScreen();
    void showInput() const;
    std::chrono::high_resolution_clock::time_point step_start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point step_stop = std::chrono::high_resolution_clock::now();
    void showStatus() const;
    void handleInput();
    void incrementCookiesOnTime();
    void buyItem(int amountToBuy, Item &item);
    bool canPayForItem(int amountToBuy, Item &item) const;
    void handleChoice(const std::string &input);
};


#endif //C_OOKIECLIKER_GAME_H
