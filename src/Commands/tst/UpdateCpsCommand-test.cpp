#include "UpdateCpsCommand.h"
#include <memory>
#include "gtest/gtest.h"

struct UpdateCpsCommandTestSuite : public ::testing::Test
{
    std::unique_ptr<Game> game;
    UpdateCpsCommandTestSuite()
    {
        game = std::make_unique<Game>();
    }

};

TEST_F(UpdateCpsCommandTestSuite, before)
{
    //assert
    ASSERT_EQ(game->getCps(), 0);
}

TEST_F(UpdateCpsCommandTestSuite, execute)
{
    //arrange
    auto buyCmd = std::make_unique<UpdateCpsCommand>(.34, game.get());

    //act
    buyCmd->execute();

    //assert
    ASSERT_EQ(game->getCps(), .34);
}

TEST_F(UpdateCpsCommandTestSuite, undo)
{
    //arrange
    auto buyCmd = std::make_unique<UpdateCpsCommand>(8.3, game.get());

    //act
    buyCmd->execute();
    buyCmd->execute();
    buyCmd->undo();

    //assert
    ASSERT_EQ(game->getCps(), 8.3);
}
