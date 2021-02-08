#include "gtest/gtest.h"
#include <memory>
#define private public
#include "GameLoop.h"

struct GameloopTestSuite : public ::testing::Test
{
    std::unique_ptr<Gameloop> game;
    std::unique_ptr<Inventory> inventory = std::make_unique<Inventory>();
    std::unique_ptr<Wallet> wallet = std::make_unique<Wallet>();
    std::unique_ptr<ItemStore> store = std::make_unique<ItemStore>();
    std::unique_ptr<notifyMessage> msg = std::make_unique<notifyMessage>();
    std::unique_ptr<MainView> gamescreen = std::make_unique<MainView>(msg.get(), wallet.get(),
                                                                      inventory.get(), store.get());
    GameloopTestSuite()
    {
        game = std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(),
                                          store.get(), gamescreen.get());
    }
};

TEST_F(GameloopTestSuite, incrementCps)
{
    game->wallet->incrementCps(CookieNumber(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    game->incrementCookiesOnTime();
    EXPECT_EQ(game->wallet->getCookieAmount(), CookieNumber(1));
}

TEST_F(GameloopTestSuite, incrementCpsLargerAmount)
{
    game->wallet->incrementCps(CookieNumber(3500));
    std::this_thread::sleep_for(std::chrono::seconds(3));
    game->incrementCookiesOnTime();
    EXPECT_EQ(game->wallet->getCookieAmount(), CookieNumber(10500));
}

//TEST_F(GameloopTestSuite, maxItemAmount)
//{
//    //arrange
//    auto game0 = std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(),
//                                            store.get(), gamescreen.get());
//    auto game1 = std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(),
//                                            store.get(), gamescreen.get());
//    auto game2 = std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(),
//                                            store.get(), gamescreen.get());
//    auto game3 = std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(),
//                                            store.get(), gamescreen.get());
//    auto game4 = std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(),
//                                            store.get(), gamescreen.get());
//
//    //act
//    game0->wallet->incrementCookieAmount(CookieNumber(15));
//
//    game1->wallet->incrementCookieAmount(CookieNumber(15 + 18));
//
//    game2->wallet->incrementCookieAmount(CookieNumber(8));
//
//    game3->wallet->incrementCookieAmount(CookieNumber(370));
//    game3->inventory->addItem("Cursor", 1);
//
//    game4->wallet->incrementCookieAmount(CookieNumber(5000));
//    game4->inventory->addItem("Cursor", 1);
//
//    //assert
//    auto result0 = game0->maxItemAmount(game1->store->getItemByName("Cursor"));
//    auto result1 = game1->maxItemAmount(game1->store->getItemByName("Cursor"));
//    auto result2 = game2->maxItemAmount(game2->store->getItemByName("Cursor"));
//    auto result3 = game3->maxItemAmount(game3->store->getItemByName("Cursor"));
//    auto result4 = game4->maxItemAmount(game4->store->getItemByName("Cursor"));
//
//    EXPECT_EQ(result0, 1);
//    EXPECT_EQ(result1, 2);
//    EXPECT_EQ(result2, 0);
//    EXPECT_EQ(result3, 10);
//    EXPECT_EQ(result4, 27);
//}

TEST_F(GameloopTestSuite, reset)
{
    //arrange
    game->wallet->incrementCookieAmount(CookieNumber(10));
    game->wallet->incrementCookieAmount(CookieNumber(20));
    game->wallet->incrementCps(CookieNumber(100));
    game->inventory->addItem("Cursor", 30);
    game->inventory->addItem("Grandma", 1);

    //act
    game->reset();

    //assert
    EXPECT_EQ(game->wallet->getCps(), 0);
    EXPECT_EQ(game->wallet->getTotalcookies(), 0);
    EXPECT_EQ(game->wallet->getCookieAmount(), 0);
    EXPECT_EQ(game->inventory->getItemCount("Cursor"), 0);
    EXPECT_EQ(game->inventory->getItemCount("Grandma"), 0);
    EXPECT_EQ(game->inventory->getLastItemAdded().empty(), true);
}