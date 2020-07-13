#include "Achievement.h"
#include <memory>
#include "gtest/gtest.h"

struct AchievementTestSuite : public ::testing::Test
{
    std::unique_ptr<Achievement> achievement;
    AchievementTestSuite()
    {
        achievement = std::make_unique<Achievement>();
    }

};

TEST_F(AchievementTestSuite, getAchievement)
{
    ASSERT_EQ(true, true);
}
