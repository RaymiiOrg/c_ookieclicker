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
    auto key = m_store->getStoreInventory().at(0);

    //act

    //assert
    EXPECT_EQ(m_store->getPrice(key, 0), CookieNumber(15));
    EXPECT_EQ(m_store->getPrice(key, 1), CookieNumber(18));
    EXPECT_EQ(m_store->getPrice(key, 2), CookieNumber(20));
    EXPECT_EQ(m_store->getPrice(key, 3), CookieNumber(23));
    EXPECT_EQ(m_store->getPrice(key, 4), CookieNumber(27));
    EXPECT_EQ(m_store->getPrice(key, 5), CookieNumber(31));
    EXPECT_EQ(m_store->getPrice(key, 6), CookieNumber(35));
    EXPECT_EQ(m_store->getPrice(key, 7), CookieNumber(40));
    EXPECT_EQ(m_store->getPrice(key, 8), CookieNumber(46));
    EXPECT_EQ(m_store->getPrice(key, 9), CookieNumber(53));
    EXPECT_EQ(m_store->getPrice(key, 10), CookieNumber(61));
}
