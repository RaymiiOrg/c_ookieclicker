#include "GameLoop.h"
#include "Wallet.h"
#include "Store.h"
#include "Inventory.h"
#include "MainView.h"
#include "notifyMessage.h"
#include <memory>



int main()
{
   std::cout << escapeCode.clearEntireScreen << escapeCode.cursorTo1x1;

    std::unique_ptr<Inventory> inventory = std::make_unique<Inventory>();
    std::unique_ptr<Wallet> wallet = std::make_unique<Wallet>();
    std::unique_ptr<Store> store = std::make_unique<Store>();
    std::unique_ptr<notifyMessage> msg = std::make_unique<notifyMessage>();
    std::unique_ptr<MainView> gamescreen = std::make_unique<MainView>(msg.get(), wallet.get(),
                                                                      inventory.get(), store.get());
    std::unique_ptr<Gameloop> game;
    game = std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(),
                                                                store.get(), gamescreen.get());
    game->start();
    return 0;
}
