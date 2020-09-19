#include "gtest/gtest.h"
#include <memory>
#define private public
#include "MainView.h"

struct ScreenTestSuite : public ::testing::Test
{
    notifyMessage msg;
    Wallet wallet;
    Store store;
    Inventory inventory;
    std::string InventoryInputKey = "2";
    std::string AchievementInputKey = "3";
    std::string OptionsInputKey = "4";
};

TEST_F(ScreenTestSuite, defaultScreen)
{
    //arrange
    MainView screen(&msg, &wallet, &inventory, &store);
    //act
    //assert
    ASSERT_EQ(screen.activeView, dynamic_cast<View *>(&screen.storeview));
}

TEST_F(ScreenTestSuite, switchScreen)
{
    //arrange
    MainView screen1(&msg, &wallet, &inventory, &store);
    MainView screen2(&msg, &wallet, &inventory, &store);
    MainView screen3(&msg, &wallet, &inventory, &store);
    //act
    screen1.handleInput(InventoryInputKey);
    screen2.handleInput(AchievementInputKey);
    screen3.handleInput(OptionsInputKey);
    //assert
    ASSERT_EQ(screen1.activeView, dynamic_cast<View *>(&screen1.inventoryview));
    ASSERT_EQ(screen2.activeView, dynamic_cast<View *>(&screen2.achievementlistview));
    ASSERT_EQ(screen3.activeView, dynamic_cast<View *>(&screen3.optionsview));
}


TEST_F(ScreenTestSuite, getItem) {
    //arrange
    MainView screen1(&msg, &wallet, &inventory, &store);
    wallet.setCookieAmount(15);
    //act
    screen1.handleInput("e");
    //assert
    ASSERT_EQ(inventory.getItemCount("Cursor"), 1);
}