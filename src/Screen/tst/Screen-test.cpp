#include <memory>
#include "gtest/gtest.h"

#define private public
#include "Screen.h"

struct ScreenTestSuite : public ::testing::Test
{
};

TEST_F(ScreenTestSuite, defaultScreen) {
    //arrange
    Screen screen;
    //act
    //assert
    ASSERT_EQ(screen.activeView, dynamic_cast<View*>(&screen.storeview));
}

TEST_F(ScreenTestSuite, switchScreen) {
    //arrange
    Screen screen1;
    Screen screen2;
    Screen screen3;
    //act
    screen1.handleInput("3");
    screen2.handleInput("4");
    screen3.handleInput("5");
    //assert
    ASSERT_EQ(screen1.activeView, dynamic_cast<View*>(&screen1.inventoryview));
    ASSERT_EQ(screen2.activeView, dynamic_cast<View*>(&screen2.achievementview));
    ASSERT_EQ(screen3.activeView, dynamic_cast<View*>(&screen3.optionsview));
}