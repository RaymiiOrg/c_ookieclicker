#include "gtest/gtest.h"
#include <memory>
#define private public
#include "AchievementList.h"
#include "Wallet.h"

struct AchievementsTestSuite : public ::testing::Test
{
    notifyMessage msg;
    AchievementList<CookieAmountAchievement> cookieAmountAchievements = AchievementList<CookieAmountAchievement>(std::vector<CookieAmountAchievement *>(), &msg);
    std::vector<AchievementMilestone> milestones{
        { CookieNumber(1),    "Wake & Bake" },
        { CookieNumber(1000), "Make some dough!" },
    };
};

TEST_F(AchievementsTestSuite, loadCookieAchievementsFromRepository)
{
    // arrange

    // act
    cookieAmountAchievements.loadFromRepository(milestones);

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
    cookieAmountAchievements.loadFromRepository(milestones);
    Wallet wallet;
    wallet.addObserver(&cookieAmountAchievements);

    // act
    wallet.incrementCookieAmount(200);

    // assert
    ASSERT_EQ(cookieAmountAchievements.getAchievements().at(0)->hasAchieved(), true);
    ASSERT_EQ(cookieAmountAchievements.getAchievements().at(1)->hasAchieved(), false);
}
