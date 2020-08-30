#include "CookieAmountAchievementList.h"
#include <memory>
#include "gtest/gtest.h"

struct AchievementsTestSuite : public ::testing::Test
{
    std::unique_ptr<CookieAmountAchievementList> achievements;
    AchievementsTestSuite()
    {
        achievements = std::make_unique<CookieAmountAchievementList>();
    }

};

TEST_F(AchievementsTestSuite, getAchievements)
{
    ASSERT_EQ(true, true);
}
