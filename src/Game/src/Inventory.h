#ifndef C_OOKIECLIKER_INVENTORY_H
#define C_OOKIECLIKER_INVENTORY_H

#include "CookieNumbers.h"
#include "Item.h"
#include <iomanip>
#include <iostream>
#include <map>

class Inventory
{
private:
    std::map<std::string, CookieNumber> m_Inventory;
    std::string last_item_added;
    CookieNumber last_item_added_amount;
    CookieNumber _cookiesPerTap = 1;

public:
    void addItem(const std::string &, const CookieNumber &amountToAdd);
    void removeItem(const std::string &, const CookieNumber &amountToRemove);
    void reset();
    CookieNumber getItemCount(const std::string &);
    CookieNumber getLastItemAddedAmount();
    CookieNumber getCookiesPerTap();
    void incrementCookiesPerTap(const CookieNumber &amount);
    const std::string &getLastItemAdded();
    const std::map<std::string, CookieNumber> &getInventory() const { return m_Inventory; };
};

#endif //C_OOKIECLIKER_INVENTORY_H
