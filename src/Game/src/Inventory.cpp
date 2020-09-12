//
// Created by remy on 20-04-20.
//

#include "Inventory.h"

void Inventory::addItem(const std::string &item, const CookieNumber &amountToAdd)
{
    bool found = false;
    for (auto &i : m_Inventory)
    {
        if (i.first == item)
        {
            i.second += amountToAdd;
            found = true;
        }
    }
    if (!found)
    {
        m_Inventory.insert(std::pair<std::string, CookieNumber>(item, amountToAdd));
    }
    last_item_added_amount = amountToAdd;
    last_item_added = item;
}

void Inventory::removeItem(const std::string &item, const CookieNumber &amountToRemove)
{
    for (auto &i : m_Inventory)
    {
        if (i.first == item)
        {
            if (i.second >= amountToRemove)
            {
                i.second -= amountToRemove;
            }
            else
            {
                i.second = CookieNumber(0);
            }
        }
    }
}

CookieNumber Inventory::getItemCount(const std::string &item)
{
    for (const auto &i : m_Inventory)
    {
        if (i.first == item)
        {
            return i.second;
        }
    }
    return CookieNumber(0);
}

CookieNumber Inventory::getLastItemAddedAmount()
{
    return last_item_added_amount;
}

const std::string &Inventory::getLastItemAdded()
{
    return last_item_added;
}

CookieNumber Inventory::getCookiesPerTap()
{
    return _cookiesPerTap;
}

void Inventory::incrementCookiesPerTap(const CookieNumber &amount)
{
    _cookiesPerTap += amount;
}

void Inventory::reset()
{
    _cookiesPerTap = 0;
    last_item_added_amount = 0;
    last_item_added.clear();
    m_Inventory.clear();
}