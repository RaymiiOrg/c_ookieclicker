#include "BuyItemCommand.h"
#include "Inventory.h"
#include "ItemStore.h"
#include "Wallet.h"
#include "gtest/gtest.h"

struct BuyTieredItemFixture : public ::testing::Test
{
    Wallet wallet;
    Inventory inventory;
    ItemStore store;

    BuyTieredItemFixture()
    {
        wallet.incrementCookieAmount(CookieNumber("100000000"));
    }

    Item &tapItem() { return store.getItemByName("Cookie Tap"); }
};

TEST_F(BuyTieredItemFixture, buyFirstTierAddsCookiesPerTap)
{
    BuyItemCommand cmd(tapItem(), CookieNumber(1), inventory, wallet, store);
    cmd.execute();
    EXPECT_EQ(inventory.getCookiesPerTap(), CookieNumber(2));
}

TEST_F(BuyTieredItemFixture, buySecondTierAddsCorrectBonus)
{
    BuyItemCommand first(tapItem(), CookieNumber(1), inventory, wallet, store);
    first.execute();
    BuyItemCommand second(tapItem(), CookieNumber(1), inventory, wallet, store);
    second.execute();
    EXPECT_EQ(inventory.getCookiesPerTap(), CookieNumber(4));
}

TEST_F(BuyTieredItemFixture, buyAllTiersAccumulatesCorrectly)
{
    for (int i = 0; i < 5; ++i) {
        BuyItemCommand cmd(tapItem(), CookieNumber(1), inventory, wallet, store);
        cmd.execute();
    }
    // 1 base + 1 + 2 + 10 + 100 + 1000 = 1114
    EXPECT_EQ(inventory.getCookiesPerTap(), CookieNumber(1114));
}

TEST_F(BuyTieredItemFixture, buyExhaustedTierDoesNothing)
{
    for (int i = 0; i < 5; ++i) {
        BuyItemCommand cmd(tapItem(), CookieNumber(1), inventory, wallet, store);
        cmd.execute();
    }
    CookieNumber tapBefore = inventory.getCookiesPerTap();
    CookieNumber cookiesBefore = wallet.getCookieAmount();
    BuyItemCommand extra(tapItem(), CookieNumber(1), inventory, wallet, store);
    extra.execute();
    EXPECT_EQ(inventory.getCookiesPerTap(), tapBefore);
    EXPECT_EQ(wallet.getCookieAmount(), cookiesBefore);
}

TEST_F(BuyTieredItemFixture, buyFirstTierDeductsCost)
{
    CookieNumber before = wallet.getCookieAmount();
    BuyItemCommand cmd(tapItem(), CookieNumber(1), inventory, wallet, store);
    cmd.execute();
    EXPECT_EQ(wallet.getCookieAmount(), before - CookieNumber(100));
}

TEST_F(BuyTieredItemFixture, undoFirstTierRestoresCookiesPerTap)
{
    BuyItemCommand cmd(tapItem(), CookieNumber(1), inventory, wallet, store);
    cmd.execute();
    cmd.undo();
    EXPECT_EQ(inventory.getCookiesPerTap(), CookieNumber(1));
}

TEST_F(BuyTieredItemFixture, undoFirstTierRefundsCost)
{
    CookieNumber before = wallet.getCookieAmount();
    BuyItemCommand cmd(tapItem(), CookieNumber(1), inventory, wallet, store);
    cmd.execute();
    cmd.undo();
    EXPECT_EQ(wallet.getCookieAmount(), before);
}

TEST_F(BuyTieredItemFixture, buyTenReturnsNoEffect)
{
    CookieNumber tapBefore = inventory.getCookiesPerTap();
    CookieNumber cookiesBefore = wallet.getCookieAmount();
    BuyItemCommand cmd(tapItem(), CookieNumber(10), inventory, wallet, store);
    cmd.execute();
    EXPECT_EQ(inventory.getCookiesPerTap(), tapBefore);
    EXPECT_EQ(wallet.getCookieAmount(), cookiesBefore);
}
