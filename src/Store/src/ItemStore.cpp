#include "ItemStore.h"

CookieNumber ItemStore::getPrice(const Item &item, const CookieNumber &amountAlreadyHave, const CookieFloater &priceIncrease)
{
    if (amountAlreadyHave == 0)
        return item.baseCost;

    CookieFloater baseCost(item.baseCost);
    CookieFloater itemAmountInInventory(amountAlreadyHave);

    auto pow = boost::multiprecision::pow(priceIncrease, itemAmountInInventory);

    auto result = boost::multiprecision::ceil(baseCost * pow);

    return CookieNumber(result);
}

CookieNumber ItemStore::getPrice(const Item &item, const CookieNumber &amountAlreadyHave)
{
    const CookieFloater priceIncrease("1.15");
    return getPrice(item, amountAlreadyHave, priceIncrease);
}

CookieNumber ItemStore::getUpgradePrice(const Item &item, unsigned int currentLevel)
{
    double upgradeFactor = 2.8;
    return getPrice(item, currentLevel, upgradeFactor);
}

CookieNumber ItemStore::getPriceOf(const Item &item, const CookieNumber &amountAlreadyHave, int amountAsked) {
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

CookieNumber ItemStore::getPriceOfTen(const Item &item, const CookieNumber &amountAlreadyHave)
{
    return getPrice(item, amountAlreadyHave) * CookieNumber(20);
}

CookieNumber ItemStore::getPriceOfHundred(const Item &item, const CookieNumber &amountAlreadyHave)
{
    return getPrice(item, amountAlreadyHave) * CookieNumber(7828749);
}

const Item &ItemStore::getItemByName(const std::string &name) const
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

