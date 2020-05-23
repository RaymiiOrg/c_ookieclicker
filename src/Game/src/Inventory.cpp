//
// Created by remy on 20-04-20.
//

#include "Inventory.h"


void Inventory::addItem(Item& item, CookieNumber amountToAdd) {
    bool found = false;
    for (auto& i : m_Inventory)
    {
        if (i.first.name == item.name)
        {
            i.second += amountToAdd;
            found = true;
        }
    }
    if (!found) {
        m_Inventory.insert(std::pair<Item &, CookieNumber>(item, amountToAdd));
    }
    last_item_added_amount = amountToAdd;
    last_item_added = item.name;
}

void Inventory::removeItem(Item &item, CookieNumber amountToRemove) {
    for (auto& i : m_Inventory)
    {
        if (i.first.name == item.name)
        {
            if (i.second >= amountToRemove) {
                i.second -= amountToRemove;
            } else {
                i.second = CookieNumber(0);
            }
        }
    }
}

CookieNumber Inventory::getItemCount(Item &item) {
    for (const auto& i : m_Inventory)
    {
        if (i.first.name == item.name)
        {
            return i.second;
        }
    }
    return CookieNumber(0);
//    if ( m_Inventory.find(item) != m_Inventory.end() ) {
//        return m_Inventory.at(item);
//    } else {
//        return CookieNumber(0);
//    }
}

CookieNumber Inventory::getLastItemAddedAmount() {
    return last_item_added_amount;
}

const std::string &Inventory::getLastItemAdded() {
    return last_item_added;
}
