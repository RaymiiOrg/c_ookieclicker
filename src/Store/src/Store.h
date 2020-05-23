//
// Created by remy on 17-05-20.
//

#ifndef C_OOKIECLIKER_Store_H
#define C_OOKIECLIKER_Store_H
#include "Item.h"

class Store {
public:
    std::vector<Item>& getStoreInventory() { return storeInventory; };
    static CookieNumber getPrice(Item& item, const CookieNumber& amount = 1);
    static void increasePrice(Item& item, const CookieNumber& amountBought = 1);
    Item& getItemByName(const std::string& name);

private:
    static CookieNumber calcPriceIncrease(Item& item, const CookieNumber& amount = 1);
    Items m_baseItems;
    std::vector<Item> storeInventory = m_baseItems.getAllItems();
};


#endif
