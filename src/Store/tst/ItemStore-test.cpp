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
