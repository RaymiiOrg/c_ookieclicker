#include "UpgradeItemCommand.h"
#include "Inventory.h"
#include "gtest/gtest.h"
#include <memory>

struct UpgradeItemCommandTestSuite : public ::testing::Test
{
    std::unique_ptr<CookieNumberPrinter> cp;
    std::unique_ptr<Inventory> inventory;
    std::unique_ptr<Wallet> wallet;
    std::unique_ptr<ItemStore> store;
    Item cursor;
    UpgradeItemCommandTestSuite()
    {
        cp = std::make_unique<CookieNumberPrinter>();
        inventory = std::make_unique<Inventory>();
        wallet = std::make_unique<Wallet>();
        store = std::make_unique<ItemStore>();
        cursor = store->getStoreInventory().at(0);
        inventory->addItem(cursor.name, 1);
    }
};

TEST_F(UpgradeItemCommandTestSuite, withoutMoney)
{
    //arrange

    //act
    auto upgradeCmd = std::make_unique<UpgradeItemCommand>(cursor,  *inventory, *wallet);
    upgradeCmd->execute();
    auto upgradeCmd2 = std::make_unique<UpgradeItemCommand>(cursor, *inventory, *wallet);
    upgradeCmd2->execute();

    //assert
    EXPECT_EQ(inventory->getLevel(cursor.name), 1);
    EXPECT_EQ(store->getUpgradePrice(cursor, inventory->getLevel(cursor.name)), 42);
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(0));
    EXPECT_EQ(wallet->getTotalcookies(), CookieNumber(0));
}

TEST_F(UpgradeItemCommandTestSuite, withMoneyOddShouldLowerBasecost)
{
    //arrange
    wallet->incrementCookieAmount(CookieNumber(300));
    auto itemBaseCostBefore = store->getItemByName(cursor.name).baseCost;

    //act
    auto upgradeCmd = std::make_unique<UpgradeItemCommand>(cursor, *inventory, *wallet);
    upgradeCmd->execute();

    //assert
    EXPECT_EQ(inventory->getLevel(cursor.name), 2);
    EXPECT_EQ(store->getUpgradePrice(cursor, inventory->getLevel(cursor.name)), 59);
    EXPECT_EQ(itemBaseCostBefore / 2, cursor.baseCost);
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(258));
    EXPECT_EQ(wallet->getTotalcookies(), CookieNumber(300));
}

TEST_F(UpgradeItemCommandTestSuite, withMoneyEvenShouldDoubleItemCPS)
{
    //arrange
    wallet->incrementCookieAmount(CookieNumber(300));
    auto itemCPSbefore = cursor.cps;


    //act
    auto upgradeCmd = std::make_unique<UpgradeItemCommand>(cursor, *inventory, *wallet);
    upgradeCmd->execute();
    upgradeCmd->execute();

    //assert
    EXPECT_EQ(inventory->getLevel(cursor.name), 3);
    EXPECT_EQ(store->getUpgradePrice(cursor, inventory->getLevel(cursor.name)), 83);
    EXPECT_EQ(itemCPSbefore * 2, cursor.cps);
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(199));
    EXPECT_EQ(wallet->getTotalcookies(), CookieNumber(300));
}

TEST_F(UpgradeItemCommandTestSuite, undo)
{
    //arrange
    wallet->incrementCookieAmount(CookieNumber(300));

    //act
    auto upgradeCmd = std::make_unique<UpgradeItemCommand>(cursor, *inventory, *wallet);
    upgradeCmd->execute();
    upgradeCmd->execute();
    upgradeCmd->undo();

    //assert
    EXPECT_EQ(inventory->getLevel(cursor.name), 1);
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(247));
    EXPECT_EQ(wallet->getTotalcookies(), CookieNumber(300));
    EXPECT_EQ(store->getUpgradePrice(cursor, inventory->getLevel(cursor.name)), 42);

}
