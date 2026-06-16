#ifndef C_OOKIECLIKER_Store_H
#define C_OOKIECLIKER_Store_H
#include "IItemStoreReader.h"
#include "IResettable.h"
#include "Item.h"

class ItemStore : public IItemStoreReader, public IResettable
{
public:
    std::vector<Item> &getStoreInventory() override { return storeInventory; };
    static CookieNumber getPrice(Item &item, const CookieNumber &amountAlreadyHave);
    static CookieNumber getPriceOf(Item &item, const CookieNumber &amountAlreadyHave, const int amountAsked);
    Item &getItemByName(const std::string &name) override;
    CookieNumber priceOf(Item &item, const CookieNumber &amountAlreadyHave, int amountAsked) override
        { return getPriceOf(item, amountAlreadyHave, amountAsked); }
    CookieNumber currentPrice(Item &item, const CookieNumber &amountAlreadyHave) override
        { return getPrice(item, amountAlreadyHave); }
    void reset() override;

private:
    Items m_baseItems;
    std::vector<Item> storeInventory = m_baseItems.getAllItems();
    static CookieNumber getPriceOfTen(Item &item, const CookieNumber &amountAlreadyHave);
    static CookieNumber getPriceOfHundred(Item &item, const CookieNumber &amountAlreadyHave);


};

#endif
