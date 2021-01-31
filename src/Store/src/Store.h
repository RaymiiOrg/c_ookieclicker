#ifndef C_OOKIECLIKER_Store_H
#define C_OOKIECLIKER_Store_H
#include "Item.h"

class Store
{
public:
    std::vector<Item> &getStoreInventory() { return storeInventory; };
    static CookieNumber getPrice(Item &item, const CookieNumber &amountAlreadyHave);
    static CookieNumber getPriceOf(Item &item, const CookieNumber &amountAlreadyHave, const int amountAsked);
    Item &getItemByName(const std::string &name);
    void reset();

private:
    Items m_baseItems;
    std::vector<Item> storeInventory = m_baseItems.getAllItems();
    static CookieNumber getPriceOfTen(Item &item, const CookieNumber &amountAlreadyHave);
    static CookieNumber getPriceOfHundred(Item &item, const CookieNumber &amountAlreadyHave);


};

#endif
