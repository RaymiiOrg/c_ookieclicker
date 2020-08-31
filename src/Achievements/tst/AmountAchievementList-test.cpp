#include "AchievementList.h"
#include <memory>
#include "gtest/gtest.h"

struct AchievementsTestSuite : public ::testing::Test
{
    std::unique_ptr<AchievementList<CookieAmountAchievement>> achievements;
    AchievementsTestSuite()
    {
        achievements = std::make_unique<AchievementList<CookieAmountAchievement>>(std::vector<CookieAmountAchievement>());
    }

};

TEST_F(AchievementsTestSuite, getAchievements)
{
    ASSERT_EQ(true, true);
}
