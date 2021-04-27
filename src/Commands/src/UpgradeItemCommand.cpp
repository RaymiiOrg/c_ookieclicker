#include "UpgradeItemCommand.h"

UpgradeItemCommand::UpgradeItemCommand(Item &item, Inventory &inventory, Wallet &wallet) :
    m_Item(item), m_Inventory(inventory), m_Wallet(wallet)
{
}

CookieNumber UpgradeItemCommand::getPriceOf()
{
    return ItemStore::getUpgradePrice(m_Item, m_Inventory.getLevel(m_Item.name));
}

void UpgradeItemCommand::execute()
{
    CookieNumber price = getPriceOf();
    if (m_Wallet.getCookieAmount() < price)
        return;

    m_Inventory.upgradeItem(m_Item.name);
    m_Wallet.decrementCookieAmount(price);
    if (m_Item.upgradeLevel % 2 == 0)
        m_Item.cps *= 2;
    else
        m_Item.baseCost /= 2;

}

void UpgradeItemCommand::undo()
{
    auto price = getPriceOf();
    if (m_Item.upgradeLevel < 1)
        return;

    --m_Item.upgradeLevel;
    m_Wallet.incrementCookieAmount(price);
    if (m_Item.upgradeLevel % 2 == 0)
        m_Item.cps /= 2;
    else
        m_Item.baseCost *= 2;
}