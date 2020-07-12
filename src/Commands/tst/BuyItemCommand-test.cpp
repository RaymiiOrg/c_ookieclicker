#include "Inventory.h"
#include "BuyItemCommand.h"
#include <memory>
#include "gtest/gtest.h"

struct BuyItemCommandTestSuite : public ::testing::Test
{
    std::unique_ptr<CookieNumberPrinter> cp;
    std::unique_ptr<Inventory> inventory;
    std::unique_ptr<Wallet> wallet;
    std::unique_ptr<Store> store;
    BuyItemCommandTestSuite()
    {
        cp = std::make_unique<CookieNumberPrinter>();
        inventory = std::make_unique<Inventory>();
        wallet = std::make_unique<Wallet>();
        store = std::make_unique<Store>();
    }

};

TEST_F(BuyItemCommandTestSuite, before)
{
    //arrange
    auto cursor = store->getStoreInventory().at(0).name;
    //assert
    EXPECT_EQ(inventory->getItemCount(cursor), CookieNumber(0));
    ASSERT_TRUE(inventory->getLastItemAdded().empty());
    EXPECT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(0));
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(0));
    EXPECT_EQ(wallet->getTotalcookies(), CookieNumber(0));
    EXPECT_EQ(wallet->getCps(), CookieNumber(0));
    EXPECT_EQ(store->getStoreInventory().at(0).baseCost, 15);
}

TEST_F(BuyItemCommandTestSuite, withoutMoney)
{
    //arrange
    auto cursor = store->getStoreInventory().at(0);

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(cursor, CookieNumber(2), *inventory, *wallet, *store);
    buyCmd->execute();
    auto buyCmd2 = std::make_unique<BuyItemCommand>(cursor, CookieNumber(1), *inventory, *wallet, *store);
    buyCmd2->execute();

    //assert
    EXPECT_EQ(inventory->getItemCount(cursor.name), CookieNumber(0));
    ASSERT_TRUE(inventory->getLastItemAdded().empty());
    EXPECT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(0));
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(0));
    EXPECT_EQ(wallet->getTotalcookies(), CookieNumber(0));
    EXPECT_EQ(wallet->getCps(), CookieNumber(0));
    EXPECT_EQ(store->getStoreInventory().at(0).baseCost, 15);
}

TEST_F(BuyItemCommandTestSuite, withMoney)
{
    //arrange
    auto cursor = store->getStoreInventory().at(0);
    wallet->incrementCookieAmount(CookieNumber(300));

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(cursor, CookieNumber(2), *inventory, *wallet, *store);
    buyCmd->execute();
    auto buyCmd2 = std::make_unique<BuyItemCommand>(cursor, CookieNumber(1), *inventory, *wallet, *store);
    buyCmd2->execute();

    //assert
    EXPECT_EQ(inventory->getItemCount(cursor.name), CookieNumber(3));
    EXPECT_EQ(inventory->getLastItemAdded(), cursor.name);
    EXPECT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(1));
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(247));
    EXPECT_EQ(wallet->getTotalcookies(), CookieNumber(300));
    EXPECT_EQ(cp->print(wallet->getCps()), cp->print(CookieNumber(0.3)));
    EXPECT_EQ(store->getPrice(cursor, inventory->getItemCount(cursor.name)), 23);
}


TEST_F(BuyItemCommandTestSuite, undo)
{
    //arrange
    auto cursor = store->getStoreInventory().at(0);
    wallet->incrementCookieAmount(CookieNumber(300));

    //act
    auto buyCmd = std::make_unique<BuyItemCommand>(cursor, CookieNumber(2), *inventory, *wallet, *store);
    buyCmd->execute();
    buyCmd->execute();
    buyCmd->undo();

    //assert
    EXPECT_EQ(inventory->getItemCount(cursor.name), CookieNumber(2));
    EXPECT_EQ(inventory->getLastItemAdded(), cursor.name);
    EXPECT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(2));
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(282));
    EXPECT_EQ(wallet->getTotalcookies(), CookieNumber(358));
    EXPECT_EQ(cp->print(wallet->getCps()), cp->print(CookieNumber(0.2)));
    EXPECT_EQ(store->getPrice(cursor, inventory->getItemCount(cursor.name)), 20);
}
