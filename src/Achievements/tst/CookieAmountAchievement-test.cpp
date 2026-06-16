#include "CookieAmountAchievement.h"
#include "Wallet.h"
#include "notifyMessage.h"
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
    CookieAmountAchievement oneCookie = CookieAmountAchievement(CookieNumber(1), "Wake & Bake", msg.get());
    CookieAmountAchievement thousandCookies = CookieAmountAchievement(CookieNumber(1000), "Make some dough", msg.get());
    wallet->addObserver(&oneCookie);
    wallet->addObserver(&thousandCookies);

    // act
    wallet->incrementCookieAmount(CookieNumber(2));

    // assert
    ASSERT_EQ(oneCookie.hasAchieved(), true);
    ASSERT_EQ(thousandCookies.hasAchieved(), false);
}

TEST_F(CookieAmountAchievementTestSuite, valueConstructor)
{
    // arrange
    CookieAmountAchievement a = CookieAmountAchievement(CookieNumber(500), "Half a thousand", msg.get());
    wallet->addObserver(&a);

    // act / assert
    wallet->incrementCookieAmount(CookieNumber(499));
    ASSERT_EQ(a.hasAchieved(), false);

    wallet->incrementCookieAmount(CookieNumber(1));
    ASSERT_EQ(a.hasAchieved(), true);
    ASSERT_EQ(a.name(), "Half a thousand");
}

TEST_F(CookieAmountAchievementTestSuite, notAchievedInitially)
{
    CookieAmountAchievement a = CookieAmountAchievement(CookieNumber(1), "First", msg.get());
    ASSERT_EQ(a.hasAchieved(), false);
}
