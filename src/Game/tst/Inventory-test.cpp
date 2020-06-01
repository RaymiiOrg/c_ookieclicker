#include "Inventory.h"
#include <memory>
#include "gtest/gtest.h"

struct InventoryTestSuite : public ::testing::Test
{
    std::unique_ptr<Inventory> inventory;
    Items items;
    InventoryTestSuite()
    {
        inventory = std::make_unique<Inventory>();
    }

};

TEST_F(InventoryTestSuite, getEmptyInventory)
{
    ASSERT_EQ(inventory->getItemCount("Key"), CookieNumber(0));
    ASSERT_EQ(inventory->getLastItemAdded().empty(), true);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(0));
    ASSERT_EQ(inventory->getInventory().empty(), true);
}

TEST_F(InventoryTestSuite, addItems)
{
    //arrange
    auto testItem1 = items.getAllItems().at(0).name;
    auto testItem2 = items.getAllItems().at(1).name;

    //act
    inventory->addItem(testItem1, CookieNumber(10));
    inventory->addItem(testItem1, CookieNumber(2));
    inventory->addItem(testItem2, CookieNumber(1));

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), CookieNumber(12));
    ASSERT_EQ(inventory->getItemCount(testItem2), CookieNumber(1));
    ASSERT_EQ(inventory->getLastItemAdded(), testItem2);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(1));
    ASSERT_EQ(inventory->getInventory().size(), 2);
}


TEST_F(InventoryTestSuite, removeItems)
{
    //arrange
    auto testItem1 = items.getAllItems().at(0).name;
    auto testItem2 = items.getAllItems().at(1).name;

    //act
    inventory->addItem(testItem1, CookieNumber(10));
    inventory->addItem(testItem1, CookieNumber(1));
    inventory->addItem(testItem2, CookieNumber(1));
    inventory->removeItem(testItem1, CookieNumber(7));
    inventory->removeItem(testItem1, CookieNumber(1));
    inventory->removeItem(testItem2, CookieNumber(7));

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), CookieNumber(3));
    ASSERT_EQ(inventory->getItemCount(testItem2), CookieNumber(0));
    ASSERT_EQ(inventory->getLastItemAdded(), testItem2);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(1));
    ASSERT_EQ(inventory->getInventory().size(), 2);
}


TEST_F(InventoryTestSuite, cookiesPerTap)
{
    //arrange / act
    inventory->incrementCookiesPerTap(340);

    //assert
    ASSERT_EQ(inventory->getCookiesPerTap(), CookieNumber(341));
}

TEST_F(InventoryTestSuite, reset)
{
    //arrange
    auto testItem1 = items.getAllItems().at(0).name;
    auto testItem2 = items.getAllItems().at(1).name;
    inventory->addItem(testItem1, CookieNumber(10));
    inventory->addItem(testItem1, CookieNumber(1));
    inventory->addItem(testItem2, CookieNumber(1));
    inventory->incrementCookiesPerTap(340);

    //act
    inventory->reset();

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), 0);
    ASSERT_EQ(inventory->getItemCount(testItem2), CookieNumber(0));
    ASSERT_EQ(inventory->getLastItemAdded().empty(), true);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(0));
    ASSERT_EQ(inventory->getCookiesPerTap(), CookieNumber(0));
    ASSERT_EQ(inventory->getInventory().size(), 0);
}