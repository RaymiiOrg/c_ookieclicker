#include "CookieAmountAchievement.h"
#include <memory>
#include "gtest/gtest.h"

struct CookieAmountAchievementTestSuite : public ::testing::Test
{
    std::unique_ptr<Wallet> wallet;
    CookieNumber amountRequired1 = CookieNumber(1);
    CookieNumber amountRequired2 = CookieNumber(1000);
    CookieAmountAchievementTestSuite()
    {
        wallet = std::make_unique<Wallet>();
    }

};

TEST_F(CookieAmountAchievementTestSuite, getAchievement)
{
    // arrange
    CookieAmountAchievement oneCookie = CookieAmountAchievement(amountRequired1, "Wake & Bake");
    CookieAmountAchievement thousandCookies = CookieAmountAchievement(amountRequired2, "Make some dough");
    wallet->addObserver(&oneCookie);
    wallet->addObserver(&thousandCookies);

    // act
    wallet->incrementCookieAmount(CookieNumber(2));

    // assert
    std::cout << oneCookie.name() << ": " << oneCookie.description() << std::endl;
    std::cout << thousandCookies.name() << ": " << thousandCookies.description() << std::endl;
    ASSERT_EQ(oneCookie.hasAchieved(), true);
    ASSERT_EQ(thousandCookies.hasAchieved(), false);
}
