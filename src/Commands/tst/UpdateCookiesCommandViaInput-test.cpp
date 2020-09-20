#include "UpdateCookiesViaInputCommand.h"
#include "gtest/gtest.h"
#include <memory>

struct UpdateCookiesViaInputCommandTestSuite : public ::testing::Test
{
    std::unique_ptr<Wallet> wallet;
    UpdateCookiesViaInputCommandTestSuite()
    {
        wallet = std::make_unique<Wallet>();
    }
};

TEST_F(UpdateCookiesViaInputCommandTestSuite, before)
{
    //assert
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(0));
}

TEST_F(UpdateCookiesViaInputCommandTestSuite, execute)
{
    //arrange
    auto buyCmd = std::make_unique<UpdateCookiesViaInputCommand>(CookieNumber(10), *wallet);

    //act
    buyCmd->execute();

    //assert
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(10));
    ASSERT_EQ(wallet->getCookiesViaInput(), CookieNumber(10));
}

TEST_F(UpdateCookiesViaInputCommandTestSuite, undo)
{
    //arrange
    auto buyCmd = std::make_unique<UpdateCookiesViaInputCommand>(CookieNumber(3), *wallet);

    //act
    buyCmd->execute();
    buyCmd->execute();
    buyCmd->undo();

    //assert
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(3));
    ASSERT_EQ(wallet->getCookiesViaInput(), CookieNumber(6));
}
