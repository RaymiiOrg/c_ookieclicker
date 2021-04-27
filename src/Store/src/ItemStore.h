#ifndef C_OOKIECLIKER_Store_H
#define C_OOKIECLIKER_Store_H
#include "Item.h"

class ItemStore
{
public:
    const std::vector<Item> &getStoreInventory() const { return storeInventory; };
    static CookieNumber getPrice(const Item &item, const CookieNumber &amountAlreadyHave);
    static CookieNumber getPrice(const Item &item, const CookieNumber &amountAlreadyHave, const CookieFloater &priceIncreasePercent);
    CookieNumber getUpgradePrice(const Item& item, unsigned int currentLevel) const;
    static CookieNumber getPriceOf(const Item &item, const CookieNumber &amountAlreadyHave, int amountAsked);
    const Item &getItemByName(const std::string &name) const;
    void reset();

private:
    Items m_baseItems;
    std::vector<Item> storeInventory = m_baseItems.getAllItems();
    static CookieNumber getPriceOfTen(const Item &item, const CookieNumber &amountAlreadyHave);
    static CookieNumber getPriceOfHundred(const Item &item, const CookieNumber &amountAlreadyHave);


};

#endif
