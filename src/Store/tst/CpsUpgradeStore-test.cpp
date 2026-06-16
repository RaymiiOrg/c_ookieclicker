#include "gtest/gtest.h"
#include "CpsUpgrade.h"

TEST(UpgradeCatalogTestSuite, cursorUpgradesExist)
{
    UpgradeCatalog store;
    const ItemCpsUpgrades *upgrades = store.getUpgradesForItem("Cursor");
    ASSERT_NE(upgrades, nullptr);
}

TEST(UpgradeCatalogTestSuite, cursorHasSevenTiers)
{
    UpgradeCatalog store;
    const ItemCpsUpgrades *upgrades = store.getUpgradesForItem("Cursor");
    ASSERT_NE(upgrades, nullptr);
    EXPECT_EQ(upgrades->tiers.size(), 7u);
}

TEST(UpgradeCatalogTestSuite, cursorBuyKeyIsE)
{
    UpgradeCatalog store;
    const ItemCpsUpgrades *upgrades = store.getUpgradesForItem("Cursor");
    ASSERT_NE(upgrades, nullptr);
    EXPECT_EQ(upgrades->buyKey, "e");
}

TEST(UpgradeCatalogTestSuite, firstTierNameIsSharpenedCursor)
{
    UpgradeCatalog store;
    const ItemCpsUpgrades *upgrades = store.getUpgradesForItem("Cursor");
    ASSERT_NE(upgrades, nullptr);
    EXPECT_EQ(upgrades->tiers[0].name, "Sharpened Cursor");
}

TEST(UpgradeCatalogTestSuite, firstTierBoostIsTen)
{
    UpgradeCatalog store;
    const ItemCpsUpgrades *upgrades = store.getUpgradesForItem("Cursor");
    ASSERT_NE(upgrades, nullptr);
    EXPECT_EQ(upgrades->tiers[0].boostPercent, CookieNumber("10"));
}

TEST(UpgradeCatalogTestSuite, lastTierNameIsOmnipotentCursor)
{
    UpgradeCatalog store;
    const ItemCpsUpgrades *upgrades = store.getUpgradesForItem("Cursor");
    ASSERT_NE(upgrades, nullptr);
    EXPECT_EQ(upgrades->tiers[6].name, "Omnipotent Cursor");
}

TEST(UpgradeCatalogTestSuite, lastTierBoostIsOneHundred)
{
    UpgradeCatalog store;
    const ItemCpsUpgrades *upgrades = store.getUpgradesForItem("Cursor");
    ASSERT_NE(upgrades, nullptr);
    EXPECT_EQ(upgrades->tiers[6].boostPercent, CookieNumber("100"));
}

TEST(UpgradeCatalogTestSuite, unknownItemReturnsNull)
{
    UpgradeCatalog store;
    EXPECT_EQ(store.getUpgradesForItem("NonExistent"), nullptr);
}

TEST(UpgradeCatalogTestSuite, firstTierCostIsOneHundred)
{
    UpgradeCatalog store;
    const ItemCpsUpgrades *upgrades = store.getUpgradesForItem("Cursor");
    ASSERT_NE(upgrades, nullptr);
    EXPECT_EQ(upgrades->tiers[0].cost, CookieNumber("100"));
}
