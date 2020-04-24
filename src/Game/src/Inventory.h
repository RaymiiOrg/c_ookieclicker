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
public:
    void addItem(const Item& item, unsigned int amountToAdd);
    void removeItem(const Item& item, unsigned int amountToRemove);
    unsigned int getItemCount(const Item &item);
    void printInventory();
};


#endif //C_OOKIECLIKER_INVENTORY_H
