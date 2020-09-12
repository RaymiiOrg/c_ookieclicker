#include "GameLoop.h"
#include "gtest/gtest.h"
#include <memory>

struct GameloopTestSuite : public ::testing::Test
{
    std::unique_ptr<Gameloop> game;
    GameloopTestSuite()
    {
        game = std::make_unique<Gameloop>(false);
    }
};

TEST_F(GameloopTestSuite, incrementCps)
{
    game->getWallet().incrementCps(CookieNumber(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    game->incrementCookiesOnTime();
    EXPECT_EQ(game->getWallet().getCookieAmount(), CookieNumber(1));
}

TEST_F(GameloopTestSuite, incrementCpsLargerAmount)
{
    game->getWallet().incrementCps(CookieNumber(3500));
    std::this_thread::sleep_for(std::chrono::seconds(3));
    game->incrementCookiesOnTime();
    EXPECT_EQ(game->getWallet().getCookieAmount(), CookieNumber(10500));
}

TEST_F(GameloopTestSuite, maxItemAmount)
{
    //arrange
    auto game0 = std::make_unique<Gameloop>(false);
    auto game1 = std::make_unique<Gameloop>(false);
    auto game2 = std::make_unique<Gameloop>(false);
    auto game3 = std::make_unique<Gameloop>(false);
    auto game4 = std::make_unique<Gameloop>(false);

    //act
    game0->getWallet().incrementCookieAmount(CookieNumber(15));

    game1->getWallet().incrementCookieAmount(CookieNumber(15 + 18));

    game2->getWallet().incrementCookieAmount(CookieNumber(8));

    game3->getWallet().incrementCookieAmount(CookieNumber(370));
    game3->getInventory().addItem("Cursor", 1);

    game4->getWallet().incrementCookieAmount(CookieNumber(5000));
    game4->getInventory().addItem("Cursor", 1);

    //assert
    auto result0 = game0->maxItemAmount(game1->getStore().getItemByName("Cursor"));
    auto result1 = game1->maxItemAmount(game1->getStore().getItemByName("Cursor"));
    auto result2 = game2->maxItemAmount(game2->getStore().getItemByName("Cursor"));
    auto result3 = game3->maxItemAmount(game3->getStore().getItemByName("Cursor"));
    auto result4 = game4->maxItemAmount(game4->getStore().getItemByName("Cursor"));

    EXPECT_EQ(result0, 1);
    EXPECT_EQ(result1, 2);
    EXPECT_EQ(result2, 0);
    EXPECT_EQ(result3, 10);
    EXPECT_EQ(result4, 27);
}

TEST_F(GameloopTestSuite, reset)
{
    //arrange
    game->getWallet().incrementCookieAmount(CookieNumber(10));
    game->getWallet().incrementCookieAmount(CookieNumber(20));
    game->getWallet().incrementCps(CookieNumber(100));
    game->getInventory().addItem("Cursor", 30);
    game->getInventory().addItem("Grandma", 1);

    //act
    game->reset();

    //assert
    EXPECT_EQ(game->getWallet().getCps(), 0);
    EXPECT_EQ(game->getWallet().getTotalcookies(), 0);
    EXPECT_EQ(game->getWallet().getCookieAmount(), 0);
    EXPECT_EQ(game->getInventory().getItemCount("Cursor"), 0);
    EXPECT_EQ(game->getInventory().getItemCount("Grandma"), 0);
    EXPECT_EQ(game->getInventory().getLastItemAdded().empty(), true);
}