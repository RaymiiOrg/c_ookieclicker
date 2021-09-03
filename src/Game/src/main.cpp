#include "GameLoop.h"
#include "Inventory.h"
#include "ItemStore.h"
#include "MainView.h"
#include "Wallet.h"
#include "cmakeConfig.h"
#include "notifyMessage.h"
#include <memory>

#ifndef USEBOOST_MPP
#include <limits>
#endif

#ifdef HAVE_WINDOWS_H
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#endif

void printNoBoostWarning()
{
#ifndef USEBOOST_MPP
    std::cout << "c_ookieclicker is compiled without boost multiprecision support. \n"
                 "This means that all the numbers (score, item amount, costs)\n"
                 "will overflow when you reach the limit of a <long double>.\n"
                 "Please read the readme (raymii.org) to find out how to compile\n"
                 "c_ookieclicker with boost support. You can still play the game,\n"
                 "but then you reach a very high score, the numbers won't fit inside\n"
                 "variables that store them, so they will revert back to zero.\n"
                 "The limit of a <long double> of this compiler is: ";
    printf("%.10Le", std::numeric_limits<long double>::max());

    std::cout << ".\n\nPress [Enter] to start the game, or CTRL+C to exit. q+[Enter] also quits.\n";
    std::string input;
    std::getline(std::cin, input);
    for (const char &c : input)
    {
        std::string choice(1, c);
        if (choice == "q")
        {
            std::cout << "So Long, and Thanks for All the Fish!\n";
            std::exit(0);
        }
    }
#endif
}

void setupWindowsConsoleVTCodes()
{
#ifdef HAVE_WINDOWS_H
    HANDLE hStdOut;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut != INVALID_HANDLE_VALUE) {
        DWORD mode;
        if (GetConsoleMode(hStdOut, &mode)) {
            if (mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) 
                std::cout << "Windows console already has ENABLE_VIRTUAL_TERMINAL_PROCESSING enabled.\n\n";
            else
            {
                mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                if (SetConsoleMode(hStdOut, mode))
                    std::cout << "Enabled ENABLE_VIRTUAL_TERMINAL_PROCESSING for Windows console.\n\n";
            }
        }
    }
    else
    {
        std::cerr << "Unable to enable ENABLE_VIRTUAL_TERMINAL_PROCESSING for Windows console.\n" <<
                     "Please make sure you are running Windows 10 1511 (build 10586) (November update) or later.\n\n";
    }
#endif
}

int main()
{
    setupWindowsConsoleVTCodes();

    printNoBoostWarning();
   
    std::cout << escapeCode.clearEntireScreen << escapeCode.cursorTo1x1;

    std::unique_ptr<Inventory> inventory = std::make_unique<Inventory>();
    std::unique_ptr<Wallet> wallet = std::make_unique<Wallet>();
    std::unique_ptr<ItemStore> store = std::make_unique<ItemStore>();
    std::unique_ptr<notifyMessage> msg = std::make_unique<notifyMessage>();
    std::unique_ptr<MainView> gamescreen = std::make_unique<MainView>(msg.get(), wallet.get(), inventory.get(), store.get());
    std::unique_ptr<Gameloop> game;
    game = std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(), store.get(), gamescreen.get());
    game->start();
    return 0;
}
