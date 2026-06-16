#include "UpgradeView.h"
#include "BuyCpsUpgradeCommand.h"
#include "BuyItemCommand.h"

void UpgradeView::render()
{
    if (!inventory || !wallet || !itemstore)
        return;

    std::cout << "Cookie Tap Upgrades:\n";
    renderCookieTapUpgrades();

    for (const auto &upgrades : cpsUpgradeStore.getUpgrades())
    {
        if (inventory->getItemCount(upgrades.targetItemName) > CookieNumber(0))
        {
            std::cout << "\n" << upgrades.targetItemName << " CPS Upgrades:\n";
            renderCpsUpgrades(upgrades.targetItemName, upgrades.targetItemName);
        }
    }
}

void UpgradeView::renderTierRow(const std::string &buyKey, const std::string &tierName,
                                const CookieNumber &cost, const std::string &boughtSuffix,
                                const std::string &nextSuffix, bool bought, bool isNext) const
{
    if (bought)
    {
        std::cout << escapeCode.terminalDim
                  << "[v] " << tierName << boughtSuffix << "\n"
                  << escapeCode.terminalReset;
    }
    else if (isNext)
    {
        bool canAfford = wallet->getCookieAmount() >= cost;
        if (!canAfford)
            std::cout << escapeCode.terminalDim;
        std::cout << "[" << buyKey << "]: " << tierName
                  << "; cost: " << cp.print(cost) << " cookies" << nextSuffix;
        if (!canAfford)
            std::cout << " (not enough cookies)" << escapeCode.terminalReset;
        std::cout << "\n";
    }
    else
    {
        std::cout << escapeCode.terminalDim
                  << "[ ] " << tierName << " (locked)\n"
                  << escapeCode.terminalReset;
    }
}

void UpgradeView::renderCookieTapUpgrades() const
{
    Item &cookieTap = itemstore->getItemByName("Cookie Tap");
    CookieNumber tierCount = inventory->getItemCount(cookieTap.name);

    for (size_t i = 0; i < cookieTap.tiers.size(); ++i)
    {
        const auto &tier = cookieTap.tiers[i];
        std::string noun = (tier.bonus == CookieNumber(1)) ? "cookie" : "cookies";
        std::string nextSuffix = "; +" + cp.print(tier.bonus) + " " + noun + " per tap";
        renderTierRow(cookieTap.buyKey, tier.name, tier.cost, "", nextSuffix,
                      CookieNumber(i) < tierCount, CookieNumber(i) == tierCount);
    }
}

void UpgradeView::renderCpsUpgrades(const std::string &itemName, const std::string &label) const
{
    const ItemCpsUpgrades *upgrades = cpsUpgradeStore.getUpgradesForItem(itemName);
    if (!upgrades)
        return;

    size_t tierCount = inventory->getCpsUpgradeTierCount(itemName);

    for (size_t i = 0; i < upgrades->tiers.size(); ++i)
    {
        const auto &tier = upgrades->tiers[i];
        std::string bonus = cp.print(tier.boostPercent) + "% " + label + " cps";
        renderTierRow(upgrades->buyKey, tier.name, tier.cost,
                      " (+" + bonus + ")", "; +" + bonus,
                      i < tierCount, i == tierCount);
    }
}

void UpgradeView::handleInput(const std::string &input)
{
    if (!wallet || !inventory || !msg || !itemstore)
        return;

    Item &cookieTap = itemstore->getItemByName("Cookie Tap");
    if (input == cookieTap.buyKey)
    {
        CookieNumber tierCount = inventory->getItemCount(cookieTap.name);
        CookieNumber price = itemstore->priceOf(cookieTap, tierCount, 1);
        if (price == CookieNumber(0))
            return;
        if (wallet->getCookieAmount() < price)
        {
            msg->setLastItemFailedToBuy(cookieTap.getDisplayName(tierCount));
            msg->setCurrentMessage(notifyMessage::msgType::NOT_ENOUGH_MONEY_FOR_ITEM);
            return;
        }
        auto buyCmd = std::make_unique<BuyItemCommand>(cookieTap, CookieNumber(1), *inventory, *wallet, *itemstore);
        buyCmd->execute();
        msg->setLastItemBoughtName(cookieTap.getDisplayName(tierCount));
        msg->setLastItemBoughtAmount(cookieTap.getTierBonus(tierCount));
        msg->setCurrentMessage(notifyMessage::msgType::BOUGHT_TAP_UPGRADE);
        return;
    }

    for (const auto &upgrades : cpsUpgradeStore.getUpgrades())
    {
        if (input != upgrades.buyKey)
            continue;
        if (inventory->getItemCount(upgrades.targetItemName) == CookieNumber(0))
            return;
        size_t tierCount = inventory->getCpsUpgradeTierCount(upgrades.targetItemName);
        if (tierCount >= upgrades.tiers.size())
            return;
        const CpsUpgrade &upgrade = upgrades.tiers[tierCount];
        if (wallet->getCookieAmount() < upgrade.cost)
        {
            msg->setLastItemFailedToBuy(upgrade.name);
            msg->setCurrentMessage(notifyMessage::msgType::NOT_ENOUGH_MONEY_FOR_ITEM);
            return;
        }
        Item &targetItem = itemstore->getItemByName(upgrades.targetItemName);
        auto buyCmd = std::make_unique<BuyCpsUpgradeCommand>(
            upgrade, upgrades.targetItemName, targetItem.cps, *inventory, *wallet);
        buyCmd->execute();
        msg->setLastItemBoughtName(upgrade.name);
        msg->setLastItemBoughtAmount(upgrade.boostPercent);
        msg->setCurrentMessage(notifyMessage::msgType::BOUGHT_CPS_UPGRADE);
        return;
    }
}
