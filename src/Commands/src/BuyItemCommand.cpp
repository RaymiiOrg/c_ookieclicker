#include "BuyItemCommand.h"

#include <utility>

BuyItemCommand::BuyItemCommand(Item &item, CookieNumber amount, Inventory &inventory, Wallet &wallet, Store &store) :
    m_Item(item), m_Amount(std::move(amount)), m_Inventory(inventory), m_Wallet(wallet), m_Store(store)
{
}

CookieNumber BuyItemCommand::getPriceOf()
{
    CookieNumber price;
    if (m_Amount == 1)
    {
        price = Store::getPriceOf(m_Item, m_Inventory.getItemCount(m_Item.name), 1);
    }
    else if (m_Amount == 10)
    {
        price = Store::getPriceOf(m_Item, m_Inventory.getItemCount(m_Item.name), 10);
    }
    else if (m_Amount == 100)
    {
        price = Store::getPriceOf(m_Item, m_Inventory.getItemCount(m_Item.name), 100);
    }
    else
    {
        for (CookieNumber i = 0; i < m_Amount; ++i)
        {
            price += Store::getPriceOf(m_Item, m_Inventory.getItemCount(m_Item.name) + i, 1);
        }
    }
    return price;
}

void BuyItemCommand::execute()
{
    CookieNumber price = getPriceOf();

    auto cps = m_Item.cps * m_Amount;
    if (m_Wallet.getCookieAmount() >= price)
    {
        m_Inventory.addItem(m_Item.name, m_Amount);
        m_Wallet.decrementCookieAmount(price);
        m_Wallet.incrementCps(cps);
    }
}

void BuyItemCommand::undo()
{
    auto price = getPriceOf();
    auto cps = m_Item.cps * m_Amount;
    m_Inventory.removeItem(m_Item.name, m_Amount);
    m_Wallet.incrementCookieAmount(price);
    m_Wallet.decrementCps(cps);
}