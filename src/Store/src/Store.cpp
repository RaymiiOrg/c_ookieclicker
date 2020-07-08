//
// Created by remy on 17-05-20.
//

#include "Store.h"


CookieNumber Store::getPrice(Item &item, const CookieNumber &amountAlreadyHave) {

    if (amountAlreadyHave == 0)
        return item.baseCost;

    CookieFloater baseCost(item.baseCost);
    CookieFloater priceIncrease("1.15");
    CookieFloater itemAmountInInventory(amountAlreadyHave);

    auto pow = boost::multiprecision::pow(priceIncrease, itemAmountInInventory);

    auto result = boost::multiprecision::ceil(baseCost * pow);

    return CookieNumber(result);
}


CookieNumber Store::getPriceOfTen(Item &item, const CookieNumber &amountAlreadyHave) {
    return getPrice(item, amountAlreadyHave) * CookieNumber(20);
}

CookieNumber Store::getPriceOfHundred(Item &item, const CookieNumber &amountAlreadyHave) {
    return getPrice(item, amountAlreadyHave) * CookieNumber(7828749);
}

Item &Store::getItemByName(const std::string& name) {
    for (auto& item : getStoreInventory()) {
        if (item.name == name) {
            return item;
        }
    }
    throw std::logic_error("Item not found");
}

void Store::reset() {
    storeInventory.clear();
    storeInventory = m_baseItems.getAllItems();
}