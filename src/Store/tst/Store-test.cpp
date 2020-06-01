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
    // arrange / act
    auto key = m_store->getStoreInventory().at(0);
    // assert
    ASSERT_EQ(m_store->getPrice(key),CookieNumber(10));
    ASSERT_EQ(m_store->getPrice(key, 5),CookieNumber(66));
    ASSERT_EQ(m_store->getPrice(key, 10),CookieNumber(131));
}

TEST_F(StoreTestSuite, priceIncrease)
{
    //arrange
    auto key = m_store->getStoreInventory().at(0);
    //act
    m_store->increasePrice(key, 1);
    //assert
    ASSERT_EQ(m_store->getPrice(key),CookieNumber(14));
}

TEST_F(StoreTestSuite, reset)
{
    //arrange
    m_store->increasePrice(m_store->getStoreInventory().at(0), 1);
    //act
    m_store->reset();
    //assert
    ASSERT_EQ(m_store->getPrice(m_store->getStoreInventory().at(0)),CookieNumber(10));
}