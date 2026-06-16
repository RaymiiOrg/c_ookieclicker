#include "gtest/gtest.h"
#define private public
#include "Inventory.h"

TEST(InventoryCpsMultiplierTestSuite, defaultMultiplierIsOne)
{
    Inventory inv;
    EXPECT_EQ(inv.getCpsMultiplier("Cursor"), CookieNumber(1));
}

TEST(InventoryCpsMultiplierTestSuite, applyTwoPercentBoostUpdatesMultiplier)
{
    Inventory inv;
    inv.applyCpsBoost("Cursor", CookieNumber("2"));
    EXPECT_EQ(inv.getCpsMultiplier("Cursor"), CookieNumber("1.02"));
}

TEST(InventoryCpsMultiplierTestSuite, applyTwoBoostsThenRevert)
{
    Inventory inv;
    inv.applyCpsBoost("Cursor", CookieNumber("2"));
    inv.applyCpsBoost("Cursor", CookieNumber("4"));
    inv.revertCpsBoost("Cursor", CookieNumber("4"));
    EXPECT_EQ(inv.getCpsMultiplier("Cursor"), CookieNumber("1.02"));
}

TEST(InventoryCpsMultiplierTestSuite, revertBoostRestoresOriginal)
{
    Inventory inv;
    inv.applyCpsBoost("Cursor", CookieNumber("2"));
    inv.revertCpsBoost("Cursor", CookieNumber("2"));
    EXPECT_EQ(inv.getCpsMultiplier("Cursor"), CookieNumber(1));
}

TEST(InventoryCpsMultiplierTestSuite, defaultTierCountIsZero)
{
    Inventory inv;
    EXPECT_EQ(inv.getCpsUpgradeTierCount("Cursor"), 0u);
}

TEST(InventoryCpsMultiplierTestSuite, incrementTierCount)
{
    Inventory inv;
    inv.incrementCpsUpgradeTier("Cursor");
    EXPECT_EQ(inv.getCpsUpgradeTierCount("Cursor"), 1u);
}

TEST(InventoryCpsMultiplierTestSuite, decrementTierCount)
{
    Inventory inv;
    inv.incrementCpsUpgradeTier("Cursor");
    inv.incrementCpsUpgradeTier("Cursor");
    inv.decrementCpsUpgradeTier("Cursor");
    EXPECT_EQ(inv.getCpsUpgradeTierCount("Cursor"), 1u);
}

TEST(InventoryCpsMultiplierTestSuite, decrementDoesNotGoBelowZero)
{
    Inventory inv;
    inv.decrementCpsUpgradeTier("Cursor");
    EXPECT_EQ(inv.getCpsUpgradeTierCount("Cursor"), 0u);
}

TEST(InventoryCpsMultiplierTestSuite, resetClearsMultipliers)
{
    Inventory inv;
    inv.applyCpsBoost("Cursor", CookieNumber("2"));
    inv.incrementCpsUpgradeTier("Cursor");
    inv.reset();
    EXPECT_EQ(inv.getCpsMultiplier("Cursor"), CookieNumber(1));
    EXPECT_EQ(inv.getCpsUpgradeTierCount("Cursor"), 0u);
}

TEST(InventoryCpsMultiplierTestSuite, multiplierIndependentPerItem)
{
    Inventory inv;
    inv.applyCpsBoost("Cursor", CookieNumber("10"));
    EXPECT_EQ(inv.getCpsMultiplier("Grandma"), CookieNumber(1));
}
