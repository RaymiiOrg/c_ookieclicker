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
    Item testItem = items.Cursor;
    ASSERT_EQ(inventory->getItemCount(testItem), 0);
}

TEST_F(InventoryTestSuite, addItems)
{
    //arrange
    Item testItem1 = items.Cursor;
    Item testItem2 = items.Grandma;

    //act
    inventory->addItem(testItem1, 10);
    inventory->addItem(testItem1, 2);
    inventory->addItem(testItem2, 1);

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), 12);
    ASSERT_EQ(inventory->getItemCount(testItem2), 1);
}


TEST_F(InventoryTestSuite, removeItems)
{
    //arrange
    Item testItem1 = items.Cursor;
    Item testItem2 = items.Grandma;

    //act
    inventory->addItem(testItem1, 10);
    inventory->addItem(testItem1, 1);
    inventory->addItem(testItem2, 1);
    inventory->removeItem(testItem1, 7);
    inventory->removeItem(testItem1, 1);
    inventory->removeItem(testItem2, 7);

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), 3);
    ASSERT_EQ(inventory->getItemCount(testItem2), 0);
}
