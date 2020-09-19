#include "CookieAmountAchievement.h"
#include "gtest/gtest.h"
#include <memory>

struct CookieAmountAchievementTestSuite : public ::testing::Test
{
    std::unique_ptr<Wallet> wallet;
    std::unique_ptr<notifyMessage> msg;
    CookieAmountAchievementTestSuite()
    {
        wallet = std::make_unique<Wallet>();
        msg = std::make_unique<notifyMessage>();
    }
};

TEST_F(CookieAmountAchievementTestSuite, getAchievement)
{
    // arrange
    CookieAmountAchievement oneCookie = CookieAmountAchievement({"1", "Wake & Bake"}, msg.get());
    CookieAmountAchievement thousandCookies = CookieAmountAchievement({"1000", "Make some dough"}, msg.get());
    wallet->addObserver(&oneCookie);
    wallet->addObserver(&thousandCookies);

    // act
    wallet->incrementCookieAmount(CookieNumber(2));

    // assert
    ASSERT_EQ(oneCookie.hasAchieved(), true);
    ASSERT_EQ(thousandCookies.hasAchieved(), false);
}
