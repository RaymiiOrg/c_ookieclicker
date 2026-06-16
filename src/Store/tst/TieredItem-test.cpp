#include "gtest/gtest.h"
#include "Item.h"
#include "ItemStore.h"

static Item makeCookieTap()
{
    Items items;
    for (auto &item : items.getAllItems())
        if (item.buyKey == "w")
            return item;
    throw std::logic_error("Cookie Tap item not found");
}

TEST(TieredItemTestSuite, cookieTapHasFiveTiers)
{
    auto item = makeCookieTap();
    EXPECT_EQ(item.tiers.size(), 5u);
}

TEST(TieredItemTestSuite, firstTierNameIsCookieUpgrade)
{
    auto item = makeCookieTap();
    EXPECT_EQ(item.tiers[0].name, "Cookie Upgrade");
}

TEST(TieredItemTestSuite, lastTierNameIsGalacticCookieUpgrade)
{
    auto item = makeCookieTap();
    EXPECT_EQ(item.tiers[4].name, "Galactic Cookie Upgrade");
}

TEST(TieredItemTestSuite, getDisplayNameAtTierZero)
{
    auto item = makeCookieTap();
    EXPECT_EQ(item.getDisplayName(CookieNumber(0)), "Cookie Upgrade");
}

TEST(TieredItemTestSuite, getDisplayNameAtTierTwo)
{
    auto item = makeCookieTap();
    EXPECT_EQ(item.getDisplayName(CookieNumber(2)), "Pro Max Cookie Upgrade");
}

TEST(TieredItemTestSuite, getTierBonusAtTierZeroIsOne)
{
    auto item = makeCookieTap();
    EXPECT_EQ(item.getTierBonus(CookieNumber(0)), CookieNumber(1));
}

TEST(TieredItemTestSuite, getTierBonusAtTierOneIsTwo)
{
    auto item = makeCookieTap();
    EXPECT_EQ(item.getTierBonus(CookieNumber(1)), CookieNumber(2));
}

TEST(TieredItemTestSuite, getTierBonusAtTierFourIsThousand)
{
    auto item = makeCookieTap();
    EXPECT_EQ(item.getTierBonus(CookieNumber(4)), CookieNumber(1000));
}

TEST(TieredItemTestSuite, getPriceAtTierZeroIsHundred)
{
    ItemStore store;
    Item &item = store.getItemByName("Cookie Tap");
    EXPECT_EQ(ItemStore::getPriceOf(item, CookieNumber(0), 1), CookieNumber(100));
}

TEST(TieredItemTestSuite, getPriceAtTierFourIs25Million)
{
    ItemStore store;
    Item &item = store.getItemByName("Cookie Tap");
    EXPECT_EQ(ItemStore::getPriceOf(item, CookieNumber(4), 1), CookieNumber(25000000));
}

TEST(TieredItemTestSuite, getPriceExhaustedReturnsZero)
{
    ItemStore store;
    Item &item = store.getItemByName("Cookie Tap");
    EXPECT_EQ(ItemStore::getPriceOf(item, CookieNumber(5), 1), CookieNumber(0));
}

TEST(TieredItemTestSuite, getPriceTenReturnsZeroForTieredItem)
{
    ItemStore store;
    Item &item = store.getItemByName("Cookie Tap");
    EXPECT_EQ(ItemStore::getPriceOf(item, CookieNumber(0), 10), CookieNumber(0));
}

TEST(TieredItemTestSuite, onlyOneCookieTapKeyInStore)
{
    ItemStore store;
    int count = 0;
    for (auto &item : store.getStoreInventory())
        if (item.buyKey == "w") ++count;
    EXPECT_EQ(count, 1);
}
