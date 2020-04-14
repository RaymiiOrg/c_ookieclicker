//
// Created by remy on 14-04-20.
//
#include "Game.h"

double Game::getCookieAmount() const {
    return cookieAmount;
}

double Game::getCps() const {
    return cps;
}

void Game::incrementCookieAmount(double amount) {
    cookieAmount += amount;
}

void Game::next_iteration() {
    update();
    render();
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
    step_start = std::chrono::high_resolution_clock::now();
    render();
    next_iteration();
}

void Game::end() {
    std::cout << "Well done. Final score: " << getCookieAmount() << "\n";
    std::cout << "Turns taken: " << stepcount << "\n";
    finished = true;
}

void Game::showInput() const
{
    std::cout << "\n===== Options ====\n";
    std::cout << "b\t\t:\t buy cookie\n";
    if(getCookieAmount() > 10)
        std::cout << "c\t\t:\t buy cursor (-10 cookies/+0.1 cps)\n";
    std::cout << "q\t\t:\t quit\n";
}

void Game::handleInput()
{    std::string input;
    std::getline(std::cin, input);
    if (input == "b")
        incrementCookieAmount();
    else if (input == "c" && getCookieAmount() > 10) {
        buyCursor();
    }
    else if (input == "q" or input == "Q") {
        end();
    }
}

void Game::showInventory() const {
    std::cout << "\n===== Inventory ====\n";
    std::cout << "Cookies\t:\t" << static_cast<int>(cookieAmount) << "\n";
    std::cout << "cps\t\t:\t" << cps << "\n";
    std::cout << "cpMs\t:\t" << (getCps()/1000) << "\n";
}

bool Game::isFinished() const {
    return finished;
}

void Game::incrementCps(double amount) {
    cps += amount;
}

void Game::incrementCookiesOnTime() {
    step_stop = std::chrono::high_resolution_clock::now();

    auto step_duration = std::chrono::duration_cast<std::chrono::milliseconds>(step_stop - step_start).count();
    auto step_duration_s = std::chrono::duration_cast<std::chrono::seconds>(step_stop - step_start).count();
    std::cout << "Step duration ms: " << step_duration << "\n";
    std::cout << "Step duration s: " << step_duration_s << "\n";

    std::cout << "Increment: " << (getCps()/1000) * step_duration << "\n";
    incrementCookieAmount((getCps()/1000) * step_duration);

    step_start = std::chrono::high_resolution_clock::now();
}

void Game::buyCursor() {
    if(getCookieAmount() > 10) {
        incrementCps(0.1);
        incrementCookieAmount(-10);
    } else {
        std::cout << "Not enough cookies to buy cursor. Have: " << getCookieAmount() << ", Need: 10.\n";
    }
}
