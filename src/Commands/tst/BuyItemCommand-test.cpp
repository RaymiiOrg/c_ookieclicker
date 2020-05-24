#include "Inventory.h"
#include "BuyItemCommand.h"
#include <memory>
#include "gtest/gtest.h"

struct BuyItemCommandTestSuite : public ::testing::Test
{
    std::unique_ptr<Inventory> inventory;
    std::unique_ptr<Wallet> wallet;
    std::unique_ptr<Store> store;
    BuyItemCommandTestSuite()
    {
        inventory = std::make_unique<Inventory>();
        wallet = std::make_unique<Wallet>();
        store = std::make_unique<Store>();
    }

};

TEST_F(BuyItemCommandTestSuite, before)
{
    //arrange
    Item testItem1 = store->getStoreInventory().at(0);
    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), CookieNumber(0));
    ASSERT_TRUE(inventory->getLastItemAdded().empty());
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(0));
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(0));
    ASSERT_EQ(wallet->getTotalcookies(), CookieNumber(0));
    ASSERT_EQ(wallet->getCps(), CookieNumber(0));
    ASSERT_EQ(store->getStoreInventory().at(0).price, 10);
}

TEST_F(BuyItemCommandTestSuite, withoutMoney)
{
    //arrange
    Item testItem1 = store->getStoreInventory().at(0);

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(testItem1, CookieNumber(2), *inventory, *wallet, *store);
    buyCmd->execute();
    auto buyCmd2 = std::make_unique<BuyItemCommand>(testItem1, CookieNumber(1), *inventory, *wallet, *store);
    buyCmd2->execute();

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), CookieNumber(0));
    ASSERT_TRUE(inventory->getLastItemAdded().empty());
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(0));
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(0));
    ASSERT_EQ(wallet->getTotalcookies(), CookieNumber(0));
    ASSERT_EQ(wallet->getCps(), CookieNumber(0));
    ASSERT_EQ(store->getStoreInventory().at(0).price, 10);
}

TEST_F(BuyItemCommandTestSuite, withMoney)
{
    //arrange
    Item testItem1 = store->getStoreInventory().at(0);
    wallet->incrementCookieAmount(CookieNumber(300));

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(testItem1, CookieNumber(2), *inventory, *wallet, *store);
    buyCmd->execute();
    auto buyCmd2 = std::make_unique<BuyItemCommand>(testItem1, CookieNumber(1), *inventory, *wallet, *store);
    buyCmd2->execute();

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), CookieNumber(3));
    ASSERT_EQ(inventory->getLastItemAdded(), testItem1.name);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(1));
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(256));
    ASSERT_EQ(wallet->getTotalcookies(), CookieNumber(300));
    ASSERT_EQ(wallet->getCps(), CookieNumber(3));
    ASSERT_EQ(store->getPrice(testItem1), 23);
}


TEST_F(BuyItemCommandTestSuite, undo)
{
    //arrange
    Item testItem1 = store->getStoreInventory().at(0);
    wallet->incrementCookieAmount(CookieNumber(300));

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(testItem1, CookieNumber(2), *inventory, *wallet, *store);
    buyCmd->execute();
    buyCmd->execute();
    buyCmd->undo();

    //assert
    ASSERT_EQ(inventory->getItemCount(testItem1), CookieNumber(2));
    ASSERT_EQ(inventory->getLastItemAdded(), testItem1.name);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(2));
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(301));
    ASSERT_EQ(wallet->getTotalcookies(), CookieNumber(373));
    ASSERT_EQ(wallet->getCps(), CookieNumber(2));
    ASSERT_EQ(store->getPrice(testItem1), 28);
}
