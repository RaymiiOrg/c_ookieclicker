#include "UpdateCookiesCommand.h"
#include <memory>
#include "gtest/gtest.h"

struct UpdateCookiesCommandTestSuite : public ::testing::Test
{
    std::unique_ptr<Wallet> wallet;
    UpdateCookiesCommandTestSuite()
    {
        wallet = std::make_unique<Wallet>();
    }

};

TEST_F(UpdateCookiesCommandTestSuite, before)
{
    //assert
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(0));
}

TEST_F(UpdateCookiesCommandTestSuite, execute)
{
    //arrange
    auto buyCmd = std::make_unique<UpdateCookiesCommand>(CookieNumber(10), *wallet);

    //act
    buyCmd->execute();

    //assert
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(10));
}

TEST_F(UpdateCookiesCommandTestSuite, undo)
{
    //arrange
    auto buyCmd = std::make_unique<UpdateCookiesCommand>(CookieNumber(3), *wallet);

    //act
    buyCmd->execute();
    buyCmd->execute();
    buyCmd->undo();

    //assert
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(3));
}
