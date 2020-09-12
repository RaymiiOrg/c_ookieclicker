//
// Created by remy on 24-04-20.
//

#include "GameLoop.h"
#include "filesystem.h"

Gameloop::Gameloop(notifyMessage* msg, Wallet* wallet, Inventory* inventory,
                   Store* store, MainView* mainview) : msg(msg), wallet(wallet), inventory(inventory),
                   store(store), gamescreen(mainview)
{
}

void Gameloop::start() {
    if (wallet && msg && store && inventory && gamescreen) {
        running = true;
        gameStepThread = std::thread(&Gameloop::gameStep, this);
        inputThread = std::thread(&Gameloop::input, this);
    }
}

Gameloop::~Gameloop()
{
    if (inputThread.joinable())
        inputThread.join();
    if (gameStepThread.joinable())
        gameStepThread.join();
}

inline void Gameloop::quit()
{
    running = false;
    showFinalScore();
}

void Gameloop::input()
{
    while (running)
    {
        std::lock_guard<std::mutex> locker(inputMutex);
        std::string input;
        std::getline(std::cin, input);
        for (char &c : input)
        {
            std::string choice(1, c);
            /** handles get cookie or quit **/
            handleGenericChoice(input);
#ifndef NDEBUG
            handleDebugChoice(input);
#endif
            if (gamescreen != nullptr)
                gamescreen->handleInput(choice);
        }
    }
}

void Gameloop::gameStep()
{
    while (running)
    {
        std::lock_guard<std::mutex> locker(gameStepMutex);
        auto startTime = std::chrono::high_resolution_clock::now();
        if (gamescreen != nullptr)
            gamescreen->render();
        else
            std::cout << "Loading screens..." << std::endl;

        // end of cycle
        if (cookieStepIncrement >= 1000)
        { //(1 second)
            incrementCookiesOnTime();
            cookieStepIncrement = 0;
        }
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsed = endTime - startTime;
        auto step_duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        if (step_duration < _maxFrameTimeMs)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(_maxFrameTimeMs - step_duration));
            cookieStepIncrement += _maxFrameTimeMs - step_duration;
        }
        else
        {
            cookieStepIncrement += step_duration;
        }
    }
}

void Gameloop::showFinalScore()
{
    std::cout << escapeCode.clearEntireScreen << escapeCode.cursorTo0x0;
    std::cout << "Well done.\n";
    if (wallet) {
        std::cout << "Ended with " << cp.print(wallet->getCookieAmount()) << " cookies." << std::endl;
        std::cout << "Total cookies earned: " << cp.print(wallet->getTotalcookies()) << std::endl;
    } else {
        std::cout << "Cant show final score, wallet is a nullptr." << std::endl;
    }
    std::cout << "Thank you for playing!\n";
    std::cout << "c_ookieclicker version: " << std::to_string(game::gameVersion);
    std::cout << " by Remy, https://raymii.org\n";
}



void Gameloop::incrementCookiesOnTime()
{
    step_stop = std::chrono::high_resolution_clock::now();
    auto step_duration = std::chrono::duration_cast<std::chrono::seconds>(step_stop - step_start).count();
    if (wallet != nullptr)
        wallet->incrementCookieAmount(wallet->getCps() * step_duration);
    step_start = std::chrono::high_resolution_clock::now();
}

void Gameloop::reset()
{
    wallet->reset();
    inventory->reset();
    store->reset();
}

void Gameloop::handleGenericChoice(const std::string &input)
{
    if (input == "c")
    {
        if (inventory && wallet) {
            auto cmd = std::make_unique<UpdateCookiesCommand>(inventory->getCookiesPerTap(), *wallet);
            cmd->execute();
        }
    }
    else if (input == "q")
    {
        quit();
    }
}

void Gameloop::handleDebugChoice(const std::string &input)
{
    if (wallet && msg) {
        if (input == "7") {
            wallet->incrementCookieAmount(CookieNumber(100));
            msg->setCurrentMessage(notifyMessage::msgType::DEBUG);
        } else if (input == "8") {
            wallet->incrementCookieAmount(wallet->getCookieAmount() * 2);
            wallet->incrementCps(wallet->getCps() * 2);
            msg->setCurrentMessage(notifyMessage::msgType::DEBUG);
        } else if (input == "9") {
            msg->setCurrentMessage(notifyMessage::msgType::DEBUG);
            CookieNumber a(
                    "115119036727821003870521051999708461"
                    "257642313059096215428937680038718894154"
                    "816459487665078480150348801009011289080");
            wallet->incrementCookieAmount(a);
            wallet->incrementCps(a * 2);
        }
    }
}
