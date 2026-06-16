#include "BuyCpsUpgradeCommand.h"
#include <utility>

BuyCpsUpgradeCommand::BuyCpsUpgradeCommand(const CpsUpgrade &upgrade,
                                           const std::string &itemName,
                                           CookieNumber itemBaseCps,
                                           IInventoryMutator &inventory,
                                           IWalletMutator &wallet)
    : m_Upgrade(upgrade),
      m_ItemName(itemName),
      m_ItemBaseCps(std::move(itemBaseCps)),
      m_Inventory(inventory),
      m_Wallet(wallet),
      m_AddedCps(0)
{
}

void BuyCpsUpgradeCommand::execute()
{
    if (m_Wallet.getCookieAmount() < m_Upgrade.cost)
        return;
    if (m_Inventory.getItemCount(m_ItemName) == CookieNumber(0))
        return;

    CookieNumber count = m_Inventory.getItemCount(m_ItemName);
    CookieNumber currentMultiplier = m_Inventory.getCpsMultiplier(m_ItemName);
    CookieNumber boostFrac = m_Upgrade.boostPercent / CookieNumber(100);
    m_AddedCps = m_ItemBaseCps * count * currentMultiplier * boostFrac;

    m_Inventory.applyCpsBoost(m_ItemName, m_Upgrade.boostPercent);
    m_Wallet.incrementCps(m_AddedCps);
    m_Inventory.incrementCpsUpgradeTier(m_ItemName);
    m_Wallet.decrementCookieAmount(m_Upgrade.cost);
}

void BuyCpsUpgradeCommand::undo()
{
    if (m_Inventory.getCpsUpgradeTierCount(m_ItemName) == 0)
        return;

    m_Inventory.revertCpsBoost(m_ItemName, m_Upgrade.boostPercent);
    m_Wallet.decrementCps(m_AddedCps);
    m_Inventory.decrementCpsUpgradeTier(m_ItemName);
    m_Wallet.incrementCookieAmount(m_Upgrade.cost);
}
