#include "UpdateCpsCommand.h"
#include "Wallet.h"
#include <memory>
#include "gtest/gtest.h"

struct UpdateCpsCommandTestSuite : public ::testing::Test
{
    std::unique_ptr<Wallet> wallet;
    UpdateCpsCommandTestSuite()
    {
        wallet = std::make_unique<Wallet>();
    }

};

TEST_F(UpdateCpsCommandTestSuite, before)
{
    //assert
    ASSERT_EQ(wallet->getCps(), CookieNumber(0));
}

TEST_F(UpdateCpsCommandTestSuite, execute)
{
    //arrange
    auto buyCmd = std::make_unique<UpdateCpsCommand>(CookieNumber(34), *wallet);

    //act
    buyCmd->execute();

    //assert
    ASSERT_EQ(wallet->getCps(), CookieNumber(34));
}

TEST_F(UpdateCpsCommandTestSuite, undo)
{
    //arrange
    auto buyCmd = std::make_unique<UpdateCpsCommand>(CookieNumber(83), *wallet);

    //act
    buyCmd->execute();
    buyCmd->execute();
    buyCmd->undo();

    //assert
    ASSERT_EQ(wallet->getCps(), CookieNumber(83));
}
