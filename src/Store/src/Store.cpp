//
// Created by remy on 17-05-20.
//

#include "Store.h"


CookieNumber Store::getPrice(Item &item, const CookieNumber& amount) {
    if (amount == 1)
        return item.price;

    auto priceXamount = item.price * amount;
    return (priceXamount + calcPriceIncrease(item, amount));
}

void Store::increasePrice(Item &item, const CookieNumber& amountBought) {
    item.price += calcPriceIncrease(item, amountBought);
}

CookieNumber Store::calcPriceIncrease(Item &item, const CookieNumber& amount) {
    auto priceIncrease = item.percentIncreaseWhenBought;
    CookieFloater itemPrice(item.price);
    auto increaseAmount = ((priceIncrease / 100) * itemPrice);
    auto resultFloat = increaseAmount * amount.convert_to<CookieFloater>();
    auto result = resultFloat.convert_to<CookieNumber>() + 1; // +1 because conversion rounds down;
    return result;
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