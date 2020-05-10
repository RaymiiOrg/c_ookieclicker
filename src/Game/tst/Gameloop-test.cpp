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
