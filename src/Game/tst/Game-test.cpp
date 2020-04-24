//
// Created by remy on 16-04-20.
//

#include "gtest/gtest.h"
#include "Game.h"

struct GameTestSuite : public ::testing::Test
{
    std::unique_ptr<Game> game;
    GameTestSuite()
    {
        game = std::make_unique<Game>();
    }

};

TEST_F(GameTestSuite, started)
{
    //arrange
    //act
    //assert
    EXPECT_FALSE(game->isFinished());
    EXPECT_EQ(game->getCookieAmount(), 0);
    EXPECT_EQ(game->getCps(), 0.0);
}