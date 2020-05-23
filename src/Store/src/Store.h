//
// Created by remy on 17-05-20.
//

#ifndef C_OOKIECLIKER_Store_H
#define C_OOKIECLIKER_Store_H
#include "Item.h"

class Store {
public:
    bool a() { return true; }
    std::vector<Item> getStoreInventory() { return storeInventory; };

private:
    Items m_baseItems;
    std::vector<Item> storeInventory = m_baseItems.getAllItems();
};


#endif
