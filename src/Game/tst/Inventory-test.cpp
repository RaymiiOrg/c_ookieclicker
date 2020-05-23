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
    Item cursor = items.getAllItems().at(0);
    ASSERT_EQ(inventory->getItemCount(cursor), CookieNumber(0));
    ASSERT_EQ(inventory->getLastItemAdded().empty(), true);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(0));
    ASSERT_EQ(inventory->getInventory().empty(), true);
}

TEST_F(InventoryTestSuite, addItems)
{
    //arrange
    Item testItem1 = items.getAllItems().at(0);
    Item testItem2 = items.getAllItems().at(1);

    //act
    inventory->addItem(testItem1, CookieNumber(10));
    inventory->addItem(testItem1, CookieNumber(2));
    inventory->addItem(testItem2, CookieNumber(1));

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), CookieNumber(12));
    ASSERT_EQ(inventory->getItemCount(testItem2), CookieNumber(1));
    ASSERT_EQ(inventory->getLastItemAdded(), testItem2.name);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(1));
    ASSERT_EQ(inventory->getInventory().size(), 2);
}


TEST_F(InventoryTestSuite, removeItems)
{
    //arrange
    Item testItem1 = items.getAllItems().at(0);
    Item testItem2 = items.getAllItems().at(1);

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
    ASSERT_EQ(inventory->getLastItemAdded(), testItem2.name);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(1));
    ASSERT_EQ(inventory->getInventory().size(), 2);
}
