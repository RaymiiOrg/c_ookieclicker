#include "ItemStore.h"
#include "gtest/gtest.h"
#include <memory>

struct StoreTestSuite : public ::testing::Test
{
    std::unique_ptr<ItemStore> itemstore;
    StoreTestSuite()
    {
        itemstore = std::make_unique<ItemStore>();
    }
};

TEST_F(StoreTestSuite, priceCalculation)
{
    //arrange
    auto cursor = itemstore->getStoreInventory().at(0);

    //act

    //assert
    EXPECT_EQ(itemstore->getPrice(cursor, 0), CookieNumber(15));
    EXPECT_EQ(itemstore->getPrice(cursor, 1), CookieNumber(18));
    EXPECT_EQ(itemstore->getPrice(cursor, 2), CookieNumber(20));
    EXPECT_EQ(itemstore->getPrice(cursor, 3), CookieNumber(23));
    EXPECT_EQ(itemstore->getPrice(cursor, 4), CookieNumber(27));
    EXPECT_EQ(itemstore->getPrice(cursor, 5), CookieNumber(31));
    EXPECT_EQ(itemstore->getPrice(cursor, 6), CookieNumber(35));
    EXPECT_EQ(itemstore->getPrice(cursor, 7), CookieNumber(40));
    EXPECT_EQ(itemstore->getPrice(cursor, 8), CookieNumber(46));
    EXPECT_EQ(itemstore->getPrice(cursor, 9), CookieNumber(53));
    EXPECT_EQ(itemstore->getPrice(cursor, 10), CookieNumber(61));
}

TEST_F(StoreTestSuite, upgradePriceCalculation)
{
    //arrange
    auto cursor = itemstore->getStoreInventory().at(0);

    //act

    //assert
    EXPECT_EQ(itemstore->getUpgradePrice(cursor, 1), CookieNumber(42));
    EXPECT_EQ(itemstore->getUpgradePrice(cursor, 2), CookieNumber(118));
    EXPECT_EQ(itemstore->getUpgradePrice(cursor, 3), CookieNumber(330));
    EXPECT_EQ(itemstore->getUpgradePrice(cursor, 4), CookieNumber(922));
    EXPECT_EQ(itemstore->getUpgradePrice(cursor, 5), CookieNumber(2582));
    EXPECT_EQ(itemstore->getUpgradePrice(cursor, 6), CookieNumber(7229));
    EXPECT_EQ(itemstore->getUpgradePrice(cursor, 7), CookieNumber(20240));
    EXPECT_EQ(itemstore->getUpgradePrice(cursor, 8), CookieNumber(56671));
    EXPECT_EQ(itemstore->getUpgradePrice(cursor, 9), CookieNumber(158677));
    EXPECT_EQ(itemstore->getUpgradePrice(cursor, 10), CookieNumber(444296));
}
