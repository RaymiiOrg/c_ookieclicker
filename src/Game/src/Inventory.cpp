#include "Inventory.h"

void Inventory::addItem(const std::string &item, const CookieNumber &amountToAdd)
{
    bool found = false;
    for (auto &i : m_Inventory)
    {
        if (i.itemName == item)
        {
            i.amount += amountToAdd;
            found = true;
        }
    }
    if (!found)
    {
        m_Inventory.push_back({item, amountToAdd, 1});
    }
    last_item_added_amount = amountToAdd;
    last_item_added = item;
}

void Inventory::removeItem(const std::string &item, const CookieNumber &amountToRemove)
{
    for (auto &i : m_Inventory)
    {
        if (i.itemName == item)
        {
            if (i.amount >= amountToRemove)
            {
                i.amount -= amountToRemove;
            }
            else
            {
                i.amount = CookieNumber(0);
            }
        }
    }
}

CookieNumber Inventory::getItemCount(const std::string &item)
{
    for (const auto &i : m_Inventory)
    {
        if (i.itemName == item)
        {
            return i.amount;
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
    _cookiesPerTap = 1;
    last_item_added_amount = 0;
    last_item_added.clear();
    m_Inventory.clear();
}
unsigned int Inventory::getLevel(const std::string itemName)
{
    if (getItemCount(itemName) == 0)
        return 0;

    for (const auto& i : m_Inventory)
    {
        if (i.itemName == itemName)
            return i.itemLevel;
    }
    return 0;

}
void Inventory::upgradeItem(const std::string &itemName)
{
    for (auto& i : m_Inventory)
    {
        if (i.itemName == itemName)
            ++i.itemLevel;
    }
}
