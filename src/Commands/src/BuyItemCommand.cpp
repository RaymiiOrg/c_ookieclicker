#include "BuyItemCommand.h"

#include <utility>

BuyItemCommand::BuyItemCommand(Item &item, CookieNumber amount, IInventoryMutator &inventory, IWalletMutator &wallet, IItemStoreReader &store) :
    m_Item(item), m_Amount(std::move(amount)), m_Inventory(inventory), m_Wallet(wallet), m_ItemStore(store)
{
}

CookieNumber BuyItemCommand::getPriceOf()
{
    CookieNumber price;
    if (m_Amount == 1)
    {
        price = m_ItemStore.priceOf(m_Item, m_Inventory.getItemCount(m_Item.name), 1);
    }
    else if (m_Amount == 10)
    {
        price = m_ItemStore.priceOf(m_Item, m_Inventory.getItemCount(m_Item.name), 10);
    }
    else if (m_Amount == 100)
    {
        price = m_ItemStore.priceOf(m_Item, m_Inventory.getItemCount(m_Item.name), 100);
    }
    else
    {
        for (CookieNumber i = 0; i < m_Amount; ++i)
        {
            price += m_ItemStore.priceOf(m_Item, m_Inventory.getItemCount(m_Item.name) + i, 1);
        }
    }
    return price;
}

void BuyItemCommand::execute()
{
    CookieNumber price = getPriceOf();
    if (price == 0)
        return;
    if (m_Wallet.getCookieAmount() < price)
        return;

    m_AddedCps = CookieNumber(0);
    m_AddedCookiesPerTap = CookieNumber(0);

    if (!m_Item.tiers.empty()) {
        int tierIdx = m_Item.tierIndexFor(m_Inventory.getItemCount(m_Item.name));
        m_Inventory.addItem(m_Item.name, m_Amount);
        m_Wallet.decrementCookieAmount(price);
        if (tierIdx >= 0)
        {
            m_AddedCookiesPerTap = m_Item.tiers[tierIdx].bonus;
            m_Inventory.incrementCookiesPerTap(m_AddedCookiesPerTap);
        }
    } else {
        m_Inventory.addItem(m_Item.name, m_Amount);
        m_Wallet.decrementCookieAmount(price);
        if (m_Item.cookiesPerTap > CookieNumber(0)) {
            m_AddedCookiesPerTap = m_Item.cookiesPerTap * m_Amount;
            m_Inventory.incrementCookiesPerTap(m_AddedCookiesPerTap);
        } else {
            m_AddedCps = m_Item.cpsGain(m_Amount, m_Inventory.getCpsMultiplier(m_Item.name));
            m_Wallet.incrementCps(m_AddedCps);
        }
    }

    // Captured for an exact undo, regardless of later state changes.
    m_PaidPrice = price;
    m_Executed = true;
}

void BuyItemCommand::undo()
{
    if (!m_Executed)
        return;

    m_Inventory.removeItem(m_Item.name, m_Amount);
    m_Wallet.incrementCookieAmount(m_PaidPrice);
    if (m_AddedCookiesPerTap > CookieNumber(0))
        m_Inventory.decrementCookiesPerTap(m_AddedCookiesPerTap);
    if (m_AddedCps > CookieNumber(0))
        m_Wallet.decrementCps(m_AddedCps);

    m_Executed = false;
}