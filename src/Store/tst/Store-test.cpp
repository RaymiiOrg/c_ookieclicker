#include "Store.h"
#include <memory>
#include "gtest/gtest.h"

struct StoreTestSuite : public ::testing::Test
{
    std::unique_ptr<Store> m_store;
    StoreTestSuite()
    {
        m_store = std::make_unique<Store>();
    }

};


TEST_F(StoreTestSuite, priceCalculation)
{
    //arrange
    auto cursor = m_store->getStoreInventory().at(0);

    //act

    //assert
    EXPECT_EQ(m_store->getPrice(cursor, 0), CookieNumber(15));
    EXPECT_EQ(m_store->getPrice(cursor, 1), CookieNumber(18));
    EXPECT_EQ(m_store->getPrice(cursor, 2), CookieNumber(20));
    EXPECT_EQ(m_store->getPrice(cursor, 3), CookieNumber(23));
    EXPECT_EQ(m_store->getPrice(cursor, 4), CookieNumber(27));
    EXPECT_EQ(m_store->getPrice(cursor, 5), CookieNumber(31));
    EXPECT_EQ(m_store->getPrice(cursor, 6), CookieNumber(35));
    EXPECT_EQ(m_store->getPrice(cursor, 7), CookieNumber(40));
    EXPECT_EQ(m_store->getPrice(cursor, 8), CookieNumber(46));
    EXPECT_EQ(m_store->getPrice(cursor, 9), CookieNumber(53));
    EXPECT_EQ(m_store->getPrice(cursor, 10), CookieNumber(61));
}
