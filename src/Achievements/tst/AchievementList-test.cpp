#include "gtest/gtest.h"
#include <memory>
#define private public
#include "AchievementList.h"

struct AchievementsTestSuite : public ::testing::Test
{
    AchievementList<CookieAmountAchievement> cookieAmountAchievements = AchievementList<CookieAmountAchievement>(std::vector<CookieAmountAchievement*>());
    fs::path current_source_file = fs::path(__FILE__);
    std::string testFileFolder = current_source_file.parent_path().string() + "/data/";
};

TEST_F(AchievementsTestSuite, loadCookieAchievementsfromCSV)
{
    // arrange

    // act
    cookieAmountAchievements.loadAchievementsFromCSV(testFileFolder + "amountachievements.csv");

    // assert
    ASSERT_EQ(cookieAmountAchievements.getAchievements().size(), 2);
    ASSERT_EQ(cookieAmountAchievements.getAchievements().at(0)->name(), "Wake & Bake");
    ASSERT_EQ(cookieAmountAchievements.getAchievements().at(1)->name(), "Make some dough!");
    ASSERT_EQ(cookieAmountAchievements.getAchievements().at(0)->_amountRequired, CookieNumber(1));
    ASSERT_EQ(cookieAmountAchievements.getAchievements().at(1)->_amountRequired, CookieNumber(1000));
}

TEST_F(AchievementsTestSuite, updateCookieAmountAchievements)
{
    // arrange
    cookieAmountAchievements.loadAchievementsFromCSV(testFileFolder + "amountachievements.csv");
    Wallet wallet;
    wallet.addObserver(&cookieAmountAchievements);

    // act
    wallet.incrementCookieAmount(200);

    // assert
    ASSERT_EQ(cookieAmountAchievements.getAchievements().at(0)->hasAchieved(), true);
    ASSERT_EQ(cookieAmountAchievements.getAchievements().at(1)->hasAchieved(), false);
}
