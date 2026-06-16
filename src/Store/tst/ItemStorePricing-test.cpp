#include "ItemStore.h"
#include "gtest/gtest.h"

struct ItemStorePricingTestSuite : public ::testing::Test
{
    ItemStore store;
    Item &cursor() { return store.getItemByName("Cursor"); }
};

TEST_F(ItemStorePricingTestSuite, priceOfOneIsBaseCost)
{
    EXPECT_EQ(store.priceOf(cursor(), CookieNumber(0), 1), CookieNumber(15));
}

TEST_F(ItemStorePricingTestSuite, priceOfTenIsTwentyTimesUnit)
{
    // getPriceOfTen = unit price * 20
    EXPECT_EQ(store.priceOf(cursor(), CookieNumber(0), 10), CookieNumber(300));
}

TEST_F(ItemStorePricingTestSuite, priceOfHundredUsesBulkMultiplier)
{
    EXPECT_EQ(store.priceOf(cursor(), CookieNumber(0), 100),
              CookieNumber(15) * CookieNumber(7828749));
}

TEST_F(ItemStorePricingTestSuite, priceOfArbitraryAmountIsUnitTimesAmount)
{
    // default branch: unit price * amount
    EXPECT_EQ(store.priceOf(cursor(), CookieNumber(0), 2), CookieNumber(30));
}

TEST_F(ItemStorePricingTestSuite, currentPriceMatchesPriceOfOne)
{
    EXPECT_EQ(store.currentPrice(cursor(), CookieNumber(0)),
              store.priceOf(cursor(), CookieNumber(0), 1));
}

TEST_F(ItemStorePricingTestSuite, getItemByNameReturnsMatch)
{
    EXPECT_EQ(store.getItemByName("Grandma").name, "Grandma");
}

TEST_F(ItemStorePricingTestSuite, getItemByNameThrowsWhenMissing)
{
    EXPECT_THROW(store.getItemByName("Nonexistent"), std::logic_error);
}

TEST_F(ItemStorePricingTestSuite, tieredItemPriceZeroForNonSingleQuantity)
{
    Item &tap = store.getItemByName("Cookie Tap");
    EXPECT_EQ(store.priceOf(tap, CookieNumber(0), 10), CookieNumber(0));
    EXPECT_EQ(store.priceOf(tap, CookieNumber(0), 100), CookieNumber(0));
}

TEST_F(ItemStorePricingTestSuite, resetRestoresFullInventory)
{
    size_t before = store.getStoreInventory().size();
    store.getStoreInventory().clear();
    ASSERT_EQ(store.getStoreInventory().size(), 0u);
    store.reset();
    EXPECT_EQ(store.getStoreInventory().size(), before);
    EXPECT_EQ(store.getItemByName("Cursor").name, "Cursor");
}
