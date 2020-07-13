#include "Wallet.h"
#include <memory>
#include "gtest/gtest.h"

struct AchievementsTestSuite : public ::testing::Test
{
    std::unique_ptr<Achievements> achievements;
    AchievementsTestSuite()
    {
        achievements = std::make_unique<Achievements>();
    }

};

TEST_F(AchievementsTestSuite, getAchievements)
{
    ASSERT_EQ(true, true);
}
