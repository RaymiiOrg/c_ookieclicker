//
// Created by remy on 14-04-20.
//
#include <algorithm>
#include "Game.h"
#include "Item.h"

void Game::next_iteration() {
    render();
    update();
}

void Game::render() {
    clearScreen();
    showStatus();
    showInput();
}

void Game::update() {
    handleInput();
    endTurn();
}

void Game::endTurn() {
    incrementCookiesOnTime();
    stepcount++;
}

void Game::start() {
    next_iteration();
}

void Game::end() {
    finished = true;
    std::cout << "Well done. Final score: " << m_Wallet->getTotalcookies() << "\n";
    std::cout << "Turns taken: " << stepcount << "\n";
}

void Game::showInput() const
{
    std::cout << "\n===== Options ====\n";
    std::cout << "↩\t:\t cookie\n";
    for (auto &item : m_Items.allItems) {
        if (m_Wallet->getCookieAmount() >= item.price)
            std::cout << item.buyOneKey << "/" << item.buyAllKey <<
                      "\t:\t buy " << item.name << "(-" <<
                      std::fixed << std::setprecision(0) << item.price << " cookies/+" <<
                      std::fixed << std::setprecision(1) << item.cps << " cps) (max: " <<
                      std::fixed << std::setprecision(0) <<
                      (int) m_Wallet->getCookieAmount() / item.price
                      << ")\n";
    }
    std::cout << "p\t:\t print inventory\n";
    std::cout << "q\t:\t quit\n";
}

void Game::handleInput()
{
    std::string input;
    std::getline(std::cin, input);
    handleChoice(input);
}

void Game::handleChoice(const std::string &input) {
    for (Item &item : m_Items.allItems) {
        if (input == item.buyOneKey) {
            buyItem(1, item);
        } else if (input == item.buyAllKey) {
            buyItem(static_cast<long long>(m_Wallet->getCookieAmount() / item.price),
                    item);
        }
    }
    if (input.empty()) {
        auto cmd = std::make_unique<UpdateCookiesCommand>(1, *m_Wallet);
        cmd->execute();
    }
    else if (input == "p") {
        m_Inventory->printInventory();
    }
    else if (input == "magic") {
        m_Wallet->incrementCookieAmount(100);
    }
    else if (input == "q" or input == "Q") {
        end();
    }
}

void Game::showStatus() const {
    std::cout << "\n===== Stats ====\n";
    std::cout << "Cookies\t:\t" << static_cast<int>(m_Wallet->getCookieAmount()) << "\n";
    std::cout << "cps\t:\t" << std::setprecision(1) << std::fixed << m_Wallet->getCps() << "\n";
}

bool Game::isFinished() const {
    return finished;
}

void Game::incrementCookiesOnTime() {
    step_stop = std::chrono::high_resolution_clock::now();
    auto step_duration = std::chrono::duration_cast<std::chrono::milliseconds>(step_stop - step_start).count();
    m_Wallet->incrementCookieAmount((m_Wallet->getCps()/1000) * step_duration);
    step_start = std::chrono::high_resolution_clock::now();
}

void Game::buyItem(int amountToBuy, Item &item) {
    if(canPayForItem(amountToBuy, item)) {
        auto buyCommand = std::make_unique<BuyItemCommand>(item, amountToBuy, *m_Inventory, *m_Wallet);
        buyCommand->execute();
        std::cout << "Bought " << amountToBuy << " " << item.name;
        if (amountToBuy > 1)
            std::cout << "s\n";
        else
            std::cout << "\n";
    } else {
        std::cout << "Not enough cookies to buy " << item.name << ". Have: " << m_Wallet->getCookieAmount() << ", Need: "
                  << item.price * amountToBuy << ".\n";
    }
}

bool Game::canPayForItem(int amountToBuy, Item &item) const
{
    return m_Wallet->getCookieAmount() >= (amountToBuy * item.price);
}

void Game::clearScreen() {
    std::cout << "\x1B[2J\x1B[H";
}

