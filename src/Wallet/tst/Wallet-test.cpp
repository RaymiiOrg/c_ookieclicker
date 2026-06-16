#include "Observer.h"
#include "Wallet.h"
#include "gtest/gtest.h"
#include <memory>

struct WalletTestSuite : public ::testing::Test
{
    std::unique_ptr<Wallet> wallet;
    WalletTestSuite()
    {
        wallet = std::make_unique<Wallet>();
    }
};

TEST_F(WalletTestSuite, getEmptyWallet)
{
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(0));
    ASSERT_EQ(wallet->getCps(), CookieNumber(0));
}

TEST_F(WalletTestSuite, incrementCookies)
{
    //arrange

    //act
    wallet->incrementCookieAmount(CookieNumber(10));
    wallet->incrementCookieAmount(CookieNumber(100));

    //assert
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(110));
}

TEST_F(WalletTestSuite, decrementCookies)
{
    //arrange

    //act
    wallet->incrementCookieAmount(CookieNumber(10));
    wallet->incrementCookieAmount(CookieNumber(100));
    wallet->decrementCookieAmount(CookieNumber(90));

    //assert
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(20));
    ASSERT_EQ(wallet->getTotalcookies(), CookieNumber(110));
}

TEST_F(WalletTestSuite, reset)
{
    //arrange

    //act
    wallet->incrementCookieAmount(CookieNumber(10));
    wallet->incrementCookieAmount(CookieNumber(100));
    wallet->reset();

    //assert
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(0));
    ASSERT_EQ(wallet->getTotalcookies(), CookieNumber(0));
}

TEST_F(WalletTestSuite, achievementBonusStartsAtZero)
{
    ASSERT_EQ(wallet->getAchievementBonusMultiplier(), CookieNumber(0));
}

TEST_F(WalletTestSuite, achievementBonusAdds)
{
    wallet->addAchievementBonus(CookieNumber("0.01"));
    ASSERT_EQ(wallet->getAchievementBonusMultiplier(), CookieNumber("0.01"));
}

TEST_F(WalletTestSuite, achievementBonusAccumulates)
{
    wallet->addAchievementBonus(CookieNumber("0.01"));
    wallet->addAchievementBonus(CookieNumber("0.01"));
    wallet->addAchievementBonus(CookieNumber("0.01"));
    ASSERT_EQ(wallet->getAchievementBonusMultiplier(), CookieNumber("0.03"));
}

TEST_F(WalletTestSuite, achievementBonusCappedAtFiftyPercent)
{
    wallet->addAchievementBonus(CookieNumber("0.4"));
    wallet->addAchievementBonus(CookieNumber("0.4"));
    ASSERT_EQ(wallet->getAchievementBonusMultiplier(), CookieNumber("0.5"));
}

TEST_F(WalletTestSuite, effectiveCpsWithoutBonus)
{
    wallet->incrementCps(CookieNumber(100));
    ASSERT_EQ(wallet->getEffectiveCps(), CookieNumber(100));
}

TEST_F(WalletTestSuite, effectiveCpsWithBonus)
{
    wallet->incrementCps(CookieNumber(100));
    wallet->addAchievementBonus(CookieNumber("0.1"));
    ASSERT_EQ(wallet->getEffectiveCps(), CookieNumber(110));
}

TEST_F(WalletTestSuite, effectiveCpsWithMaxBonus)
{
    wallet->incrementCps(CookieNumber(100));
    wallet->addAchievementBonus(CookieNumber("1.0"));
    ASSERT_EQ(wallet->getEffectiveCps(), CookieNumber(150));
}

TEST_F(WalletTestSuite, achievementBonusResetOnReset)
{
    wallet->addAchievementBonus(CookieNumber("0.1"));
    wallet->reset();
    ASSERT_EQ(wallet->getAchievementBonusMultiplier(), CookieNumber(0));
    ASSERT_EQ(wallet->getEffectiveCps(), CookieNumber(0));
}
