//
// Created by remy on 14-04-20.
//
#include "Game.h"

long double Game::getCookieAmount() const {
    return cookieAmount;
}

long double Game::getCps() const {
    return cps;
}

void Game::incrementCookieAmount(long double amount) {
    cookieAmount += amount;
    if (amount > 0)
        totalcookies += static_cast<long long>(amount);
}

void Game::next_iteration() {
    render();
    update();
}

void Game::render() {
    showInventory();
    showInput();
}

void Game::update() {
    handleInput();
    incrementCookiesOnTime();
    stepcount++;
}

void Game::start() {
    next_iteration();
}

void Game::end() {
    finished = true;
    std::cout << "Well done. Final score: " << totalcookies << "\n";
    std::cout << "Turns taken: " << stepcount << "\n";
}

void Game::showInput() const
{
    std::cout << "\n===== Options ====\n";
    std::cout << "b\t:\t buy cookie\n";
    if(getCookieAmount() > 10)
        std::cout << "c\t:\t buy cursor (-10 cookies/+0.1 cps) (max: " << (int)getCookieAmount() / 10 << ")\n";
    std::cout << "q\t:\t quit\n";
}

void Game::handleInput()
{    std::string input;
    std::getline(std::cin, input);
    if (input == "b")
        incrementCookieAmount();
    else if (input == "c" && getCookieAmount() > 10) {
        buyCursor(1);
    }
    else if (input == "C" && getCookieAmount() > 20) {
        buyCursor((int)getCookieAmount()/10);
    }
    else if (input == "magic") {
        incrementCookieAmount(99999999);
        buyCursor(999999);
    }
    else if (input == "q" or input == "Q") {
        end();
    }
}

void Game::showInventory() const {
    std::cout << "\n===== Inventory ====\n";
    std::cout << "Cookies\t:\t" << static_cast<int>(getCookieAmount()) << "\n";
    std::cout << "cps\t:\t" << std::fixed << cps << "\n";
}

bool Game::isFinished() const {
    return finished;
}

void Game::incrementCps(long double amount) {
    cps += amount;
}

void Game::incrementCookiesOnTime() {
    step_stop = std::chrono::high_resolution_clock::now();
    auto step_duration = std::chrono::duration_cast<std::chrono::milliseconds>(step_stop - step_start).count();
    incrementCookieAmount((getCps()/1000) * step_duration);
    step_start = std::chrono::high_resolution_clock::now();
}

void Game::buyCursor(int amount) {
    if(getCookieAmount() >= (amount*10)) {
        std::cout << "Bought " << amount << " cursor(s)\n";
        incrementCps(0.1*amount);
        incrementCookieAmount((-10*amount));
    } else {
        std::cout << "Not enough cookies to buy cursor. Have: " << getCookieAmount() << ", Need: "
        << 10*amount << ".\n";
    }
}

