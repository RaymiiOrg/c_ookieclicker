//
// Created by remy on 20-04-20.
//

#ifndef C_OOKIECLIKER_INVENTORY_H
#define C_OOKIECLIKER_INVENTORY_H

#include "Item.h"
#include "CookieNumbers.h"
#include <iostream>
#include <iomanip>
#include <map>

class Inventory {
private:
    std::map<Item, CookieNumber> m_Inventory;
    std::string last_item_added;
    CookieNumber last_item_added_amount;

public:
    void addItem(Item& item, CookieNumber amountToAdd);
    void removeItem(Item& item, CookieNumber amountToRemove);
    CookieNumber getItemCount(Item &item);
    CookieNumber getLastItemAddedAmount();
    const std::string& getLastItemAdded();
    std::map<Item, CookieNumber>& getInventory() { return m_Inventory; };
};


#endif //C_OOKIECLIKER_INVENTORY_H
