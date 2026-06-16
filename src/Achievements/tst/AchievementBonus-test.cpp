#include "AchievementList.h"
#include "CookieAmountAchievement.h"
#include "CookiesPerSecondAchievement.h"
#include "CookiesViaInputAchievement.h"
#include "Wallet.h"
#include "gtest/gtest.h"
#include <memory>

struct AchievementBonusTestSuite : public ::testing::Test
{
    std::unique_ptr<Wallet> wallet;
    std::unique_ptr<notifyMessage> msg;
    AchievementBonusTestSuite()
    {
        wallet = std::make_unique<Wallet>();
        msg = std::make_unique<notifyMessage>();
    }
};

TEST_F(AchievementBonusTestSuite, noUnlockedMeansNoBonus)
{
    // arrange
    AchievementList<CookieAmountAchievement> list(std::vector<CookieAmountAchievement *>(), msg.get());
    list.loadFromRepository({{ CookieNumber("1000"), "First" }});
    wallet->addObserver(&list);

    // act — not enough to unlock
    wallet->incrementCookieAmount(CookieNumber(1));

    // assert
    ASSERT_EQ(wallet->getAchievementBonusMultiplier(), CookieNumber(0));
}

TEST_F(AchievementBonusTestSuite, oneUnlockAddsOnePctBonus)
{
    // arrange
    AchievementList<CookieAmountAchievement> list(std::vector<CookieAmountAchievement *>(), msg.get());
    list.loadFromRepository({{ CookieNumber("10"), "Ten cookies" }});
    wallet->addObserver(&list);

    // act
    wallet->incrementCookieAmount(CookieNumber(10));

    // assert
    ASSERT_EQ(wallet->getAchievementBonusMultiplier(), CookieNumber("0.01"));
}

TEST_F(AchievementBonusTestSuite, twoUnlocksAddsTwoPctBonus)
{
    // arrange
    AchievementList<CookieAmountAchievement> list(std::vector<CookieAmountAchievement *>(), msg.get());
    list.loadFromRepository({
        { CookieNumber("10"),   "Ten cookies" },
        { CookieNumber("100"),  "Hundred cookies" },
    });
    wallet->addObserver(&list);

    // act — unlock both in one increment
    wallet->incrementCookieAmount(CookieNumber(100));

    // assert
    ASSERT_EQ(wallet->getAchievementBonusMultiplier(), CookieNumber("0.02"));
}

TEST_F(AchievementBonusTestSuite, bonusNotAddedTwiceForSameAchievement)
{
    // arrange
    AchievementList<CookieAmountAchievement> list(std::vector<CookieAmountAchievement *>(), msg.get());
    list.loadFromRepository({{ CookieNumber("10"), "Ten cookies" }});
    wallet->addObserver(&list);

    // act — two increments, first one unlocks, second should not double-count
    wallet->incrementCookieAmount(CookieNumber(10));
    wallet->incrementCookieAmount(CookieNumber(10));

    // assert
    ASSERT_EQ(wallet->getAchievementBonusMultiplier(), CookieNumber("0.01"));
}

TEST_F(AchievementBonusTestSuite, bonusFromMultipleLists)
{
    // arrange
    AchievementList<CookieAmountAchievement> amountList(std::vector<CookieAmountAchievement *>(), msg.get());
    amountList.loadFromRepository({{ CookieNumber("1"), "First cookie" }});

    AchievementList<CookiesPerSecondAchievement> cpsList(std::vector<CookiesPerSecondAchievement *>(), msg.get());
    cpsList.loadFromRepository({{ CookieNumber("1"), "First cps" }});

    wallet->addObserver(&amountList);
    wallet->addObserver(&cpsList);

    // act
    wallet->incrementCookieAmount(CookieNumber(1));
    wallet->incrementCps(CookieNumber(1));

    // assert — one unlock from each list = 2% total
    ASSERT_EQ(wallet->getAchievementBonusMultiplier(), CookieNumber("0.02"));
}

TEST_F(AchievementBonusTestSuite, effectiveCpsReflectsBonus)
{
    // arrange
    AchievementList<CookiesPerSecondAchievement> list(std::vector<CookiesPerSecondAchievement *>(), msg.get());
    list.loadFromRepository({{ CookieNumber("100"), "Speed baker" }});
    wallet->addObserver(&list);

    wallet->incrementCps(CookieNumber(100)); // also triggers unlock

    // assert — cps=100, bonus=1% => effective = 101
    ASSERT_EQ(wallet->getEffectiveCps(), CookieNumber(101));
}

TEST_F(AchievementBonusTestSuite, bonusCappedAtFiftyPct)
{
    // arrange — load 60 milestones, each worth 1%, to exceed the cap
    std::vector<AchievementMilestone> milestones;
    CookieNumber amount(1);
    for (int i = 0; i < 60; ++i)
    {
        milestones.push_back({ amount, "Achievement " + std::to_string(i) });
        amount = amount * CookieNumber(10);
    }

    AchievementList<CookieAmountAchievement> list(std::vector<CookieAmountAchievement *>(), msg.get());
    list.loadFromRepository(milestones);
    wallet->addObserver(&list);

    // act — unlock all 60
    wallet->incrementCookieAmount(amount);

    // assert — capped at 50%
    ASSERT_EQ(wallet->getAchievementBonusMultiplier(), CookieNumber("0.5"));
}

TEST_F(AchievementBonusTestSuite, cpsViaInputAchievementUnlocksBonus)
{
    // arrange
    AchievementList<CookiesViaInputAchievement> list(std::vector<CookiesViaInputAchievement *>(), msg.get());
    list.loadFromRepository({{ CookieNumber("10"), "Nice Keyboard!" }});
    wallet->addObserver(&list);

    // act
    wallet->incrementCookieViaInput(CookieNumber(10));

    // assert
    ASSERT_EQ(wallet->getAchievementBonusMultiplier(), CookieNumber("0.01"));
}
