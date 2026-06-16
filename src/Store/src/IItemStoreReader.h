#ifndef C_OOKIECLIKER_IITEMSTOREREADER_H
#define C_OOKIECLIKER_IITEMSTOREREADER_H

#include "Item.h"

class IItemStoreReader
{
public:
    virtual ~IItemStoreReader() = default;
    virtual std::vector<Item> &getStoreInventory() = 0;
    virtual Item &getItemByName(const std::string &name) = 0;
    virtual CookieNumber priceOf(Item &item, const CookieNumber &amountAlreadyHave, int amountAsked) = 0;
    virtual CookieNumber currentPrice(Item &item, const CookieNumber &amountAlreadyHave) = 0;
};

#endif //C_OOKIECLIKER_IITEMSTOREREADER_H
