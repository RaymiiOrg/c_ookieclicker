//
// Created by remy on 20-04-20.
//

#ifndef C_OOKIECLIKER_INVENTORY_H
#define C_OOKIECLIKER_INVENTORY_H

#include "Item.h"
#include <iostream>
#include <iomanip>
#include <map>

class Inventory {
private:
    std::map<Item, CookieNumber> m_Inventory;
    std::string last_item_added;
    CookieNumber last_item_added_amount;

public:
    void addItem(const Item& item, const CookieNumber& amountToAdd);
    void removeItem(const Item& item, const CookieNumber& amountToRemove);
    CookieNumber getItemCount(const Item &item);
    CookieNumber getLastItemAddedAmount() const;
    const std::string &getLastItemAdded() const;
};


#endif //C_OOKIECLIKER_INVENTORY_H
