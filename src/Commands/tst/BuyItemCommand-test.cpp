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
    ASSERT_EQ(inventory->getItemCount(testItem1), CookieNumber(0));
    ASSERT_TRUE(inventory->getLastItemAdded().empty());
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(0));
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(0));
    ASSERT_EQ(wallet->getTotalcookies(), CookieNumber(0));
    ASSERT_EQ(wallet->getCps(), CookieNumber(0));
}

TEST_F(BuyItemCommandTestSuite, withoutMoney)
{
    //arrange
    Item testItem1 = items.Cursor;

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(testItem1, CookieNumber(2), *inventory, *wallet);
    buyCmd->execute();
    auto buyCmd2 = std::make_unique<BuyItemCommand>(testItem1, CookieNumber(1), *inventory, *wallet);
    buyCmd2->execute();

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), CookieNumber(0));
    ASSERT_TRUE(inventory->getLastItemAdded().empty());
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(0));
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(0));
    ASSERT_EQ(wallet->getTotalcookies(), CookieNumber(0));
    ASSERT_EQ(wallet->getCps(), CookieNumber(0));
}

TEST_F(BuyItemCommandTestSuite, withMoney)
{
    //arrange
    Item testItem1 = items.Cursor;
    wallet->incrementCookieAmount(CookieNumber(300));

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(testItem1, CookieNumber(2), *inventory, *wallet);
    buyCmd->execute();
    auto buyCmd2 = std::make_unique<BuyItemCommand>(testItem1, CookieNumber(1), *inventory, *wallet);
    buyCmd2->execute();

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), CookieNumber(3));
    ASSERT_EQ(inventory->getLastItemAdded(), testItem1.name);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(1));
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(270));
    ASSERT_EQ(wallet->getTotalcookies(), CookieNumber(300));
    ASSERT_EQ(wallet->getCps(), CookieNumber(3));
}


TEST_F(BuyItemCommandTestSuite, undo)
{
    //arrange
    Item testItem1 = items.Cursor;
    wallet->incrementCookieAmount(CookieNumber(300));

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(testItem1, CookieNumber(2), *inventory, *wallet);
    buyCmd->execute();
    buyCmd->execute();
    buyCmd->undo();

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), CookieNumber(2));
    ASSERT_EQ(inventory->getLastItemAdded(), testItem1.name);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(2));
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(280));
    ASSERT_EQ(wallet->getTotalcookies(), CookieNumber(320));
    ASSERT_EQ(wallet->getCps(), CookieNumber(2));
}
