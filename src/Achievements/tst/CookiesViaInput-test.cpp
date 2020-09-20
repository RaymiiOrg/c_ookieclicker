#include "CookiesViaInputAchievement.h"
#include "Wallet.h"
#include "gtest/gtest.h"
#include <memory>

struct CookiesViaInputAchievementTestSuite : public ::testing::Test
{
    std::unique_ptr<Wallet> wallet;
    std::unique_ptr<notifyMessage> msg;
    CookiesViaInputAchievementTestSuite()
    {
        wallet = std::make_unique<Wallet>();
        msg = std::make_unique<notifyMessage>();
    }
};

TEST_F(CookiesViaInputAchievementTestSuite, getAchievement)
{
    // arrange
    CookiesViaInputAchievement tenCookies = CookiesViaInputAchievement({"10", "Test 1"}, msg.get());
    CookiesViaInputAchievement aHundredCookies = CookiesViaInputAchievement({"100", "Test 2"}, msg.get());
    wallet->addObserver(&tenCookies);
    wallet->addObserver(&aHundredCookies);

    // act
    wallet->incrementCookieViaInput(CookieNumber(9));
    wallet->incrementCookieAmount(CookieNumber(911));
    wallet->incrementCookieViaInput(CookieNumber(20));

    // assert
    ASSERT_EQ(tenCookies.hasAchieved(), true);
    ASSERT_EQ(aHundredCookies.hasAchieved(), false);
}
