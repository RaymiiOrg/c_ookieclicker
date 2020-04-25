#include "Inventory.h"
#include "BuyItemCommand.h"
#include <memory>
#include "gtest/gtest.h"

struct BuyItemCommandTestSuite : public ::testing::Test
{
    std::unique_ptr<Inventory> inventory;
    std::unique_ptr<Wallet> wallet;
    Items items;
    BuyItemCommandTestSuite()
    {
        inventory = std::make_unique<Inventory>();
        wallet = std::make_unique<Wallet>();
    }

};

TEST_F(BuyItemCommandTestSuite, before)
{
    //arrange
    Item testItem1 = items.Cursor;
    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), 0);
    ASSERT_TRUE(inventory->getLastItemAdded().empty());
    ASSERT_EQ(inventory->getLastItemAddedAmount(), 0);
    ASSERT_EQ(wallet->getCookieAmount(), 0);
    ASSERT_EQ(wallet->getTotalcookies(), 0);
    ASSERT_EQ(wallet->getCps(), 0);
}

TEST_F(BuyItemCommandTestSuite, withoutMoney)
{
    //arrange
    Item testItem1 = items.Cursor;

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(testItem1, 2, *inventory, *wallet);
    buyCmd->execute();
    auto buyCmd2 = std::make_unique<BuyItemCommand>(testItem1, 1, *inventory, *wallet);
    buyCmd2->execute();

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), 0);
    ASSERT_TRUE(inventory->getLastItemAdded().empty());
    ASSERT_EQ(inventory->getLastItemAddedAmount(), 0);
    ASSERT_EQ(wallet->getCookieAmount(), 0);
    ASSERT_EQ(wallet->getTotalcookies(), 0);
    ASSERT_EQ(wallet->getCps(), 0);
}

TEST_F(BuyItemCommandTestSuite, withMoney)
{
    //arrange
    Item testItem1 = items.Cursor;
    wallet->incrementCookieAmount(300);

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(testItem1, 2, *inventory, *wallet);
    buyCmd->execute();
    auto buyCmd2 = std::make_unique<BuyItemCommand>(testItem1, 1, *inventory, *wallet);
    buyCmd2->execute();

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), 3);
    ASSERT_EQ(inventory->getLastItemAdded(), testItem1.name);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), 1);
    ASSERT_EQ(wallet->getCookieAmount(), 270);
    ASSERT_EQ(wallet->getTotalcookies(), 300);
    ASSERT_DOUBLE_EQ(wallet->getCps(), 0.3);
}


TEST_F(BuyItemCommandTestSuite, undo)
{
    //arrange
    Item testItem1 = items.Cursor;
    wallet->incrementCookieAmount(300);

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(testItem1, 2, *inventory, *wallet);
    buyCmd->execute();
    buyCmd->execute();
    buyCmd->undo();

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), 2);
    ASSERT_EQ(inventory->getLastItemAdded(), testItem1.name);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), 2);
    ASSERT_EQ(wallet->getCookieAmount(), 280);
    ASSERT_EQ(wallet->getTotalcookies(), 320);
    ASSERT_NEAR(wallet->getCps(), 0.3, 0.1);
}
