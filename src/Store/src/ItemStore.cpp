#include "ItemStore.h"

CookieNumber ItemStore::getPrice(Item &item, const CookieNumber &amountAlreadyHave)
{

    if (amountAlreadyHave == 0)
        return item.baseCost;

    CookieFloater baseCost(item.baseCost);
    CookieFloater priceIncrease("1.15");
    CookieFloater itemAmountInInventory(amountAlreadyHave);

    auto pow = boost::multiprecision::pow(priceIncrease, itemAmountInInventory);

    auto result = boost::multiprecision::ceil(baseCost * pow);

    return CookieNumber(result);
}

CookieNumber ItemStore::getPriceOf(Item &item, const CookieNumber &amountAlreadyHave, int amountAsked) {
    switch (amountAsked) {
        case 1:
            return getPrice(item, amountAlreadyHave);
        case 10:
            return getPriceOfTen(item, amountAlreadyHave);
        case 100:
            return getPriceOfHundred(item, amountAlreadyHave);
        default:
            return getPrice(item, amountAlreadyHave) * amountAsked;
    }
}

CookieNumber ItemStore::getPriceOfTen(Item &item, const CookieNumber &amountAlreadyHave)
{
    return getPrice(item, amountAlreadyHave) * CookieNumber(20);
}

CookieNumber ItemStore::getPriceOfHundred(Item &item, const CookieNumber &amountAlreadyHave)
{
    return getPrice(item, amountAlreadyHave) * CookieNumber(7828749);
}

Item &ItemStore::getItemByName(const std::string &name)
{
    for (auto &item : getStoreInventory())
    {
        if (item.name == name)
        {
            return item;
        }
    }
    throw std::logic_error("Item not found");
}

void ItemStore::reset()
{
    storeInventory.clear();
    storeInventory = m_baseItems.getAllItems();
}