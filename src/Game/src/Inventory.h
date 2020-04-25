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
    std::map<Item, unsigned int> m_Inventory;
    std::string last_item_added;
    unsigned int last_item_added_amount;

public:
    void addItem(const Item& item, unsigned int amountToAdd);
    void removeItem(const Item& item, unsigned int amountToRemove);
    unsigned int getItemCount(const Item &item);
    unsigned int getLastItemAddedAmount() const;
    const std::string &getLastItemAdded() const;
};


#endif //C_OOKIECLIKER_INVENTORY_H
