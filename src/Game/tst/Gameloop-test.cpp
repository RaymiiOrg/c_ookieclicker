#include <memory>
#include "gtest/gtest.h"
#include "GameLoop.h"

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
    ASSERT_EQ(game->getWallet().getCookieAmount(), CookieNumber(1));
}

TEST_F(GameloopTestSuite, maxItemAmount)
{
    auto game1 = std::make_unique<Gameloop>(false);
    auto game2 = std::make_unique<Gameloop>(false);
    auto game3 = std::make_unique<Gameloop>(false);
    auto game4 = std::make_unique<Gameloop>(false);

    game1->getWallet().incrementCookieAmount(CookieNumber(10));
    game2->getWallet().incrementCookieAmount(CookieNumber(20));
    game3->getWallet().incrementCookieAmount(CookieNumber(29));
    game4->getWallet().incrementCookieAmount(CookieNumber(100));


    auto result = game1->maxItemAmount(game1->getStore().getItemByName("Cursor"));
    auto result2 = game2->maxItemAmount(game2->getStore().getItemByName("Cursor"));
    auto result3 = game3->maxItemAmount(game3->getStore().getItemByName("Cursor"));
    auto result4 = game4->maxItemAmount(game4->getStore().getItemByName("Cursor"));

    ASSERT_EQ(result, 1);
    ASSERT_EQ(result2, 1);
    ASSERT_EQ(result3, 2);
    ASSERT_EQ(result4, 7);
}
