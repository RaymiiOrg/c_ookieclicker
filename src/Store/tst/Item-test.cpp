#include "Item.h"
#include "gtest/gtest.h"
#include <memory>

struct ItemTestSuite : public ::testing::Test
{
    std::unique_ptr<Items> items;
    ItemTestSuite()
    {
        items = std::make_unique<Items>();
    }
};

TEST_F(ItemTestSuite, cookieKeyNotAllowedAsItemKey)
{
    //arrange
    std::string CookieKey = "c";
    bool stringFound = false;

    //act
    for (const auto& item : items->getAllItems())
    {
        if (item.buyKey == CookieKey)
        {
            stringFound = true;
        }
    }
    //assert
    ASSERT_FALSE(stringFound);
}


TEST_F(ItemTestSuite, noDoubleItemKeys)
{
    //arrange
    auto allItems = items->getAllItems();
    std::vector<std::string> allItemKeys;
    for (const auto& item : allItems) {
        allItemKeys.push_back(item.buyKey);
    }

    //act
    sort(allItemKeys.begin(), allItemKeys.end());
    auto it = std::unique(allItemKeys.begin(), allItemKeys.end() );
    bool noDuplicateItemKeys = (it == allItemKeys.end() );

    //assert
    ASSERT_FALSE(noDuplicateItemKeys);
}
