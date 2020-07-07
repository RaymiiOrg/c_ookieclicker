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
    auto key = store->getStoreInventory().at(0).name;
    //assert
    ASSERT_EQ(inventory->getItemCount(key), CookieNumber(0));
    ASSERT_TRUE(inventory->getLastItemAdded().empty());
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(0));
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(0));
    ASSERT_EQ(wallet->getTotalcookies(), CookieNumber(0));
    ASSERT_EQ(wallet->getCps(), CookieNumber(0));
    ASSERT_EQ(store->getStoreInventory().at(0).baseCost, 15);
}

TEST_F(BuyItemCommandTestSuite, withoutMoney)
{
    //arrange
    auto key = store->getStoreInventory().at(0);

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(key, CookieNumber(2), *inventory, *wallet, *store);
    buyCmd->execute();
    auto buyCmd2 = std::make_unique<BuyItemCommand>(key, CookieNumber(1), *inventory, *wallet, *store);
    buyCmd2->execute();

    //assert
    ASSERT_EQ(inventory->getItemCount(key.name), CookieNumber(0));
    ASSERT_TRUE(inventory->getLastItemAdded().empty());
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(0));
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(0));
    ASSERT_EQ(wallet->getTotalcookies(), CookieNumber(0));
    ASSERT_EQ(wallet->getCps(), CookieNumber(0));
    ASSERT_EQ(store->getStoreInventory().at(0).baseCost, 15);
}

TEST_F(BuyItemCommandTestSuite, withMoney)
{
    //arrange
    auto key = store->getStoreInventory().at(0);
    wallet->incrementCookieAmount(CookieNumber(300));

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(key, CookieNumber(2), *inventory, *wallet, *store);
    buyCmd->execute();
    auto buyCmd2 = std::make_unique<BuyItemCommand>(key, CookieNumber(1), *inventory, *wallet, *store);
    buyCmd2->execute();

    //assert
    ASSERT_EQ(inventory->getItemCount(key.name), CookieNumber(3));
    ASSERT_EQ(inventory->getLastItemAdded(), key.name);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(1));
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(265));
    ASSERT_EQ(wallet->getTotalcookies(), CookieNumber(300));
    ASSERT_EQ(wallet->getCps(), CookieNumber(3));
    ASSERT_EQ(store->getPrice(key, 1, inventory->getItemCount(key.name)), 23);
}


TEST_F(BuyItemCommandTestSuite, undo)
{
    //arrange
    auto key = store->getStoreInventory().at(0);
    wallet->incrementCookieAmount(CookieNumber(300));

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(key, CookieNumber(2), *inventory, *wallet, *store);
    buyCmd->execute();
    buyCmd->execute();
    buyCmd->undo();

    //assert
    ASSERT_EQ(inventory->getItemCount(key.name), CookieNumber(2));
    ASSERT_EQ(inventory->getLastItemAdded(), key.name);
    ASSERT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(2));
    ASSERT_EQ(wallet->getCookieAmount(), CookieNumber(298));
    ASSERT_EQ(wallet->getTotalcookies(), CookieNumber(353));
    ASSERT_EQ(wallet->getCps(), CookieNumber(2));
    ASSERT_EQ(store->getPrice(key, 1, inventory->getItemCount(key.name)), 20);
}
