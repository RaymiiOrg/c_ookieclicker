#include "gtest/gtest.h"
#define private public
#include "BuyCpsUpgradeCommand.h"
#include "Inventory.h"
#include "Wallet.h"
#include "CpsUpgrade.h"

class BuyCpsUpgradeCommandTestSuite : public ::testing::Test
{
protected:
    std::unique_ptr<Inventory> inventory;
    std::unique_ptr<Wallet> wallet;
    CpsUpgrade upgrade2pct{"Sharpened Cursor", CookieNumber("100"), CookieNumber("2")};
    CpsUpgrade upgrade4pct{"Gilded Cursor",    CookieNumber("1000"), CookieNumber("4")};
    CookieNumber cursorCps{".1"};

    void SetUp() override
    {
        inventory = std::make_unique<Inventory>();
        wallet = std::make_unique<Wallet>();
    }
};

TEST_F(BuyCpsUpgradeCommandTestSuite, executeWithoutMoneydoesNothing)
{
    inventory->addItem("Cursor", CookieNumber(5));
    auto cmd = std::make_unique<BuyCpsUpgradeCommand>(upgrade2pct, "Cursor", cursorCps, *inventory, *wallet);
    cmd->execute();
    EXPECT_EQ(wallet->getCps(), CookieNumber(0));
    EXPECT_EQ(inventory->getCpsMultiplier("Cursor"), CookieNumber(1));
    EXPECT_EQ(inventory->getCpsUpgradeTierCount("Cursor"), 0u);
}

TEST_F(BuyCpsUpgradeCommandTestSuite, executeWithoutCursorsDoesNothing)
{
    wallet->incrementCookieAmount(CookieNumber("1000"));
    auto cmd = std::make_unique<BuyCpsUpgradeCommand>(upgrade2pct, "Cursor", cursorCps, *inventory, *wallet);
    cmd->execute();
    EXPECT_EQ(wallet->getCps(), CookieNumber(0));
    EXPECT_EQ(inventory->getCpsMultiplier("Cursor"), CookieNumber(1));
}

TEST_F(BuyCpsUpgradeCommandTestSuite, executeDeductsCost)
{
    wallet->incrementCookieAmount(CookieNumber("200"));
    inventory->addItem("Cursor", CookieNumber(1));
    auto cmd = std::make_unique<BuyCpsUpgradeCommand>(upgrade2pct, "Cursor", cursorCps, *inventory, *wallet);
    cmd->execute();
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber("100"));
}

TEST_F(BuyCpsUpgradeCommandTestSuite, executeWithOneCursorAddsTwoPercentCps)
{
    // 1 cursor at 0.1 cps, 2% boost: adds 0.1 * 1 * 1.0 * 0.02 = 0.002
    wallet->incrementCookieAmount(CookieNumber("200"));
    inventory->addItem("Cursor", CookieNumber(1));
    wallet->incrementCps(cursorCps); // simulate cursor already contributing cps
    auto cmd = std::make_unique<BuyCpsUpgradeCommand>(upgrade2pct, "Cursor", cursorCps, *inventory, *wallet);
    cmd->execute();
    EXPECT_EQ(wallet->getCps(), cursorCps + CookieNumber("0.002"));
}

TEST_F(BuyCpsUpgradeCommandTestSuite, executeUpdatesMultiplier)
{
    wallet->incrementCookieAmount(CookieNumber("200"));
    inventory->addItem("Cursor", CookieNumber(1));
    auto cmd = std::make_unique<BuyCpsUpgradeCommand>(upgrade2pct, "Cursor", cursorCps, *inventory, *wallet);
    cmd->execute();
    EXPECT_EQ(inventory->getCpsMultiplier("Cursor"), CookieNumber("1.02"));
}

TEST_F(BuyCpsUpgradeCommandTestSuite, executeIncreasesTierCount)
{
    wallet->incrementCookieAmount(CookieNumber("200"));
    inventory->addItem("Cursor", CookieNumber(1));
    auto cmd = std::make_unique<BuyCpsUpgradeCommand>(upgrade2pct, "Cursor", cursorCps, *inventory, *wallet);
    cmd->execute();
    EXPECT_EQ(inventory->getCpsUpgradeTierCount("Cursor"), 1u);
}

TEST_F(BuyCpsUpgradeCommandTestSuite, undoRestoresMultiplier)
{
    wallet->incrementCookieAmount(CookieNumber("200"));
    inventory->addItem("Cursor", CookieNumber(1));
    auto cmd = std::make_unique<BuyCpsUpgradeCommand>(upgrade2pct, "Cursor", cursorCps, *inventory, *wallet);
    cmd->execute();
    cmd->undo();
    EXPECT_EQ(inventory->getCpsMultiplier("Cursor"), CookieNumber(1));
}

TEST_F(BuyCpsUpgradeCommandTestSuite, undoRestoresCps)
{
    wallet->incrementCookieAmount(CookieNumber("200"));
    inventory->addItem("Cursor", CookieNumber(1));
    wallet->incrementCps(cursorCps);
    auto cmd = std::make_unique<BuyCpsUpgradeCommand>(upgrade2pct, "Cursor", cursorCps, *inventory, *wallet);
    cmd->execute();
    cmd->undo();
    EXPECT_EQ(wallet->getCps(), cursorCps);
}

TEST_F(BuyCpsUpgradeCommandTestSuite, undoRefundsCost)
{
    wallet->incrementCookieAmount(CookieNumber("200"));
    inventory->addItem("Cursor", CookieNumber(1));
    auto cmd = std::make_unique<BuyCpsUpgradeCommand>(upgrade2pct, "Cursor", cursorCps, *inventory, *wallet);
    cmd->execute();
    cmd->undo();
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber("200"));
}

TEST_F(BuyCpsUpgradeCommandTestSuite, undoDecreasesTierCount)
{
    wallet->incrementCookieAmount(CookieNumber("200"));
    inventory->addItem("Cursor", CookieNumber(1));
    auto cmd = std::make_unique<BuyCpsUpgradeCommand>(upgrade2pct, "Cursor", cursorCps, *inventory, *wallet);
    cmd->execute();
    cmd->undo();
    EXPECT_EQ(inventory->getCpsUpgradeTierCount("Cursor"), 0u);
}

TEST_F(BuyCpsUpgradeCommandTestSuite, secondUpgradeCompoundsOnFirst)
{
    // After 2% boost, multiplier = 1.02. Then 4% of that:
    // addedCps2 = baseCps * 1.02 * 0.04
    wallet->incrementCookieAmount(CookieNumber("2000"));
    inventory->addItem("Cursor", CookieNumber(10));
    auto cmd1 = std::make_unique<BuyCpsUpgradeCommand>(upgrade2pct, "Cursor", cursorCps, *inventory, *wallet);
    cmd1->execute();
    auto cmd2 = std::make_unique<BuyCpsUpgradeCommand>(upgrade4pct, "Cursor", cursorCps, *inventory, *wallet);
    cmd2->execute();
    // multiplier after both: 1.02 * 1.04 = 1.0608
    EXPECT_EQ(inventory->getCpsMultiplier("Cursor"), CookieNumber("1.02") * CookieNumber("1.04"));
    EXPECT_EQ(inventory->getCpsUpgradeTierCount("Cursor"), 2u);
}
