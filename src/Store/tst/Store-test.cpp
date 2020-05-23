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

TEST_F(StoreTestSuite, getEmptyStore)
{
    ASSERT_EQ(m_store->a(), true);
}
