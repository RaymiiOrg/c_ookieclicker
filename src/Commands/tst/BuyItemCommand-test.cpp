#include "BuyItemCommand.h"
#include "Inventory.h"
#include "ItemStore.h"
#include "Wallet.h"
#include "gtest/gtest.h"
#include <memory>

struct BuyItemCommandTestSuite : public ::testing::Test
{
    std::unique_ptr<CookieNumberPrinter> cp;
    std::unique_ptr<Inventory> inventory;
    std::unique_ptr<Wallet> wallet;
    std::unique_ptr<ItemStore> store;
    BuyItemCommandTestSuite()
    {
        cp = std::make_unique<CookieNumberPrinter>();
        inventory = std::make_unique<Inventory>();
        wallet = std::make_unique<Wallet>();
        store = std::make_unique<ItemStore>();
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
    EXPECT_EQ(inventory->getItemCount(cursor.name), CookieNumber());
    ASSERT_TRUE(inventory->getLastItemAdded().empty());
    EXPECT_EQ(inventory->getLastItemAddedAmount(), CookieNumber());
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber());
    EXPECT_EQ(wallet->getTotalcookies(), CookieNumber());
    EXPECT_EQ(wallet->getCps(), CookieNumber());
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
    EXPECT_EQ(cp->print(wallet->getCps()), cp->print(CookieNumber(0.31)));
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
    // undo refunds exactly the price paid by the execute it reverses (the 2nd
    // execute: getPrice(2)+getPrice(3) = 20+23 = 43), not the price recomputed
    // at the post-purchase count. 224 + 43 = 267, total 300 + 43 = 343.
    EXPECT_EQ(inventory->getItemCount(cursor.name), CookieNumber(2));
    EXPECT_EQ(inventory->getLastItemAdded(), cursor.name);
    EXPECT_EQ(inventory->getLastItemAddedAmount(), CookieNumber(2));
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(267));
    EXPECT_EQ(wallet->getTotalcookies(), CookieNumber(343));
    EXPECT_EQ(cp->print(wallet->getCps()), cp->print(CookieNumber(0.2)));
    EXPECT_EQ(store->getPrice(cursor, inventory->getItemCount(cursor.name)), 20);
}

TEST_F(BuyItemCommandTestSuite, undoRemovesExactCpsEvenAfterMultiplierChange)
{
    //arrange
    auto cursor = store->getStoreInventory().at(0);
    wallet->incrementCookieAmount(CookieNumber(1000));

    //act: buy a cursor, then a CPS upgrade raises the cursor multiplier, then undo
    auto buyCmd = std::make_unique<BuyItemCommand>(cursor, CookieNumber(1), *inventory, *wallet, *store);
    buyCmd->execute();
    inventory->applyCpsBoost(cursor.name, CookieNumber(100)); // multiplier doubles going forward
    buyCmd->undo();

    //assert: undo removes exactly the CPS execute added (pre-boost), so CPS is back to 0
    EXPECT_EQ(wallet->getCps(), CookieNumber(0));
}
