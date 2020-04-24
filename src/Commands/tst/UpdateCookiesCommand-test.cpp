#include "UpdateCookiesCommand.h"
#include <memory>
#include "gtest/gtest.h"

struct UpdateCookiesCommandTestSuite : public ::testing::Test
{
    std::unique_ptr<Game> game;
    UpdateCookiesCommandTestSuite()
    {
        game = std::make_unique<Game>();
    }

};

TEST_F(UpdateCookiesCommandTestSuite, before)
{
    //assert
    ASSERT_EQ(game->getCookieAmount(), 0);
}

TEST_F(UpdateCookiesCommandTestSuite, execute)
{
    //arrange
    auto buyCmd = std::make_unique<UpdateCookiesCommand>(10, game.get());

    //act
    buyCmd->execute();

    //assert
    ASSERT_EQ(game->getCookieAmount(), 10);
}

TEST_F(UpdateCookiesCommandTestSuite, undo)
{
    //arrange
    auto buyCmd = std::make_unique<UpdateCookiesCommand>(3, game.get());

    //act
    buyCmd->execute();
    buyCmd->execute();
    buyCmd->undo();

    //assert
    ASSERT_EQ(game->getCookieAmount(), 3);
}
