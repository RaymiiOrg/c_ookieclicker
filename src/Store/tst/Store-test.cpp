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

TEST_F(StoreTestSuite, getPriceNothingBought)
{
    auto cursor = m_store->getStoreInventory().at(0);
    ASSERT_EQ(m_store->getPrice(cursor),CookieNumber(10));
    ASSERT_EQ(m_store->getPrice(cursor, 5),CookieNumber(65));
    ASSERT_EQ(m_store->getPrice(cursor, 10),CookieNumber(130));
}

TEST_F(StoreTestSuite, priceIncrease)
{
    auto cursor = m_store->getStoreInventory().at(0);
    m_store->increasePrice(cursor, 1);
    ASSERT_EQ(m_store->getPrice(cursor),CookieNumber(13));

}