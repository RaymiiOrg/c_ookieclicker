#include "Wallet.h"
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
    ASSERT_EQ(wallet->getCookieAmount(), 0);
    ASSERT_EQ(wallet->getCps(), 0);
}

TEST_F(WalletTestSuite, incrementCookies)
{
    //arrange

    //act
    wallet->incrementCookieAmount(10);
    wallet->incrementCookieAmount(100);

    //assert
    ASSERT_EQ(wallet->getCookieAmount(), 110);
}

