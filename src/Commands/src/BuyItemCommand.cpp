//
// Created by remy on 20-04-20.
//

#include "BuyItemCommand.h"

BuyItemCommand::BuyItemCommand(Item &item, CookieNumber amount, Inventory &inventory, Wallet &wallet, Store &store) :
    m_Item(item), m_Amount(amount), m_Inventory(inventory), m_Wallet(wallet), m_Store(store)
{
}

CookieNumber BuyItemCommand::getPriceOf()
{
    CookieNumber price;
    if (m_Amount == 1)
    {
        price = Store::getPrice(m_Item, m_Inventory.getItemCount(m_Item.name));
    }
    else if (m_Amount == 10)
    {
        price = Store::getPriceOfTen(m_Item, m_Inventory.getItemCount(m_Item.name));
    }
    else if (m_Amount == 100)
    {
        price = Store::getPriceOfHundred(m_Item, m_Inventory.getItemCount(m_Item.name));
    }
    else
    {
        for (CookieNumber i = 0; i < m_Amount; ++i)
        {
            price += Store::getPrice(m_Item, m_Inventory.getItemCount(m_Item.name) + i);
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