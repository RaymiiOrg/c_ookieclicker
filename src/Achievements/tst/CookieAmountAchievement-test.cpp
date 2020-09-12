#include "CookieAmountAchievement.h"
#include "gtest/gtest.h"
#include <memory>

struct CookieAmountAchievementTestSuite : public ::testing::Test
{
    std::unique_ptr<Wallet> wallet;
    CookieAmountAchievementTestSuite()
    {
        wallet = std::make_unique<Wallet>();
    }
};

TEST_F(CookieAmountAchievementTestSuite, getAchievement)
{
    // arrange
    CookieAmountAchievement oneCookie = CookieAmountAchievement({"1", "Wake & Bake"});
    CookieAmountAchievement thousandCookies = CookieAmountAchievement({"1000", "Make some dough"});
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
