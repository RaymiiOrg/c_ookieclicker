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
    CookieNumber _cookiesPerTap = 1;

public:
    void addItem(Item& item, CookieNumber amountToAdd);
    void removeItem(Item& item, CookieNumber amountToRemove);
    void reset();
    CookieNumber getItemCount(Item &item);
    CookieNumber getLastItemAddedAmount();
    CookieNumber getCookiesPerTap();
    void incrementCookiesPerTap(CookieNumber amount);
    const std::string& getLastItemAdded();
    std::map<Item, CookieNumber>& getInventory() { return m_Inventory; };
};


#endif //C_OOKIECLIKER_INVENTORY_H
