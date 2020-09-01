#include "Wallet.h"
#include "Observer.h"
#include <memory>
#include "gtest/gtest.h"

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

