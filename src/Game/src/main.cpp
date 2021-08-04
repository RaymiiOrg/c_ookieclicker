#include "GameLoop.h"
#include "Inventory.h"
#include "ItemStore.h"
#include "MainView.h"
#include "Wallet.h"
#include "notifyMessage.h"
#include "cmakeConfig.h"
#include <memory>
#ifndef USEBOOST_MPP
#include <limits>
#endif

void printNoBoostWarning() {
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

    std::cout << ".\n\nPress any key to start the game, or CTRL+C to exit.\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
#endif
}

int main()
{
    std::cout << escapeCode.clearEntireScreen << escapeCode.cursorTo1x1;

    printNoBoostWarning();

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


