#include "Store.h"
#include <memory>
#include "gtest/gtest.h"

struct StoreTestSuite : public ::testing::Test
{
    std::unique_ptr<Store> Store;
    StoreTestSuite()
    {
        Store = std::make_unique<Store>();
    }

};

TEST_F(StoreTestSuite, getEmptyStore)
{
    ASSERT_EQ(Store->a(), true);
}
