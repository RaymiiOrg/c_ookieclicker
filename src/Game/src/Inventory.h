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
    struct itemSlot {
        std::string itemName;
        CookieNumber amount;
        unsigned int itemLevel;
    };
    std::vector<itemSlot> m_Inventory;
    std::string last_item_added;
    CookieNumber last_item_added_amount;
    CookieNumber _cookiesPerTap = 1;

public:
    void addItem(const std::string &itemName, const CookieNumber &amountToAdd);
    void removeItem(const std::string &itemName, const CookieNumber &amountToRemove);
    void reset();
    CookieNumber getItemCount(const std::string &);
    CookieNumber getLastItemAddedAmount();
    CookieNumber getCookiesPerTap();
    void incrementCookiesPerTap(const CookieNumber &amount);
    void upgradeItem(const std::string& itemName);
    const std::string &getLastItemAdded();
    const std::vector<itemSlot> &getInventory() const { return m_Inventory; };
    unsigned int getLevel(const std::string itemName);
};

#endif //C_OOKIECLIKER_INVENTORY_H
