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

CookieNumber Inventory::getItemCount(const std::string &item) const
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

CookieNumber Inventory::getCookiesPerTap() const
{
    return _cookiesPerTap;
}

void Inventory::incrementCookiesPerTap(const CookieNumber &amount)
{
    _cookiesPerTap += amount;
}

void Inventory::decrementCookiesPerTap(const CookieNumber &amount)
{
    if (_cookiesPerTap > amount)
        _cookiesPerTap -= amount;
    else
        _cookiesPerTap = 1;
}

void Inventory::reset()
{
    _cookiesPerTap = 1;
    last_item_added_amount = 0;
    last_item_added.clear();
    m_Inventory.clear();
    _cpsMultipliers.clear();
    _cpsUpgradeTierCounts.clear();
}

CookieNumber Inventory::getCpsMultiplier(const std::string &itemName) const
{
    auto it = _cpsMultipliers.find(itemName);
    return (it != _cpsMultipliers.end()) ? it->second : CookieNumber(1);
}

void Inventory::applyCpsBoost(const std::string &itemName, const CookieNumber &boostPercent)
{
    CookieNumber current = getCpsMultiplier(itemName);
    _cpsMultipliers[itemName] = current * (CookieNumber(1) + boostPercent / CookieNumber(100));
}

void Inventory::revertCpsBoost(const std::string &itemName, const CookieNumber &boostPercent)
{
    CookieNumber current = getCpsMultiplier(itemName);
    _cpsMultipliers[itemName] = current / (CookieNumber(1) + boostPercent / CookieNumber(100));
}

size_t Inventory::getCpsUpgradeTierCount(const std::string &itemName) const
{
    auto it = _cpsUpgradeTierCounts.find(itemName);
    return (it != _cpsUpgradeTierCounts.end()) ? it->second : 0;
}

void Inventory::incrementCpsUpgradeTier(const std::string &itemName)
{
    _cpsUpgradeTierCounts[itemName]++;
}

void Inventory::decrementCpsUpgradeTier(const std::string &itemName)
{
    auto it = _cpsUpgradeTierCounts.find(itemName);
    if (it != _cpsUpgradeTierCounts.end() && it->second > 0)
        it->second--;
}