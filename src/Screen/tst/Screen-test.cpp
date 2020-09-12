#include <memory>
#include "gtest/gtest.h"
#define private public
#include "Screen.h"

struct ScreenTestSuite : public ::testing::Test {
    notifyMessage msg;
    Wallet wallet;
    Store store;
    Inventory inventory;
    std::string InventoryInputKey = "2";
    std::string AchievementInputKey = "3";
    std::string OptionsInputKey = "4";
};

TEST_F(ScreenTestSuite, defaultScreen) {
    //arrange
    Screen screen(&wallet, &msg, &inventory, &store);
    //act
    //assert
    ASSERT_EQ(screen.activeView, dynamic_cast<View *>(&screen.storeview));
}

TEST_F(ScreenTestSuite, switchScreen) {
    //arrange
    Screen screen1(&wallet, &msg, &inventory, &store);
    Screen screen2(&wallet, &msg, &inventory, &store);
    Screen screen3(&wallet, &msg, &inventory, &store);
    //act
    screen1.handleInput(InventoryInputKey);
    screen2.handleInput(AchievementInputKey);
    screen3.handleInput(OptionsInputKey);
    //assert
    ASSERT_EQ(screen1.activeView, dynamic_cast<View *>(&screen1.inventoryview));
    ASSERT_EQ(screen2.activeView, dynamic_cast<View *>(&screen2.achievementlistview));
    ASSERT_EQ(screen3.activeView, dynamic_cast<View *>(&screen3.optionsview));
}