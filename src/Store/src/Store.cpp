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
