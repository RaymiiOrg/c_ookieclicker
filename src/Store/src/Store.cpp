//
// Created by remy on 17-05-20.
//

#include "Store.h"


CookieNumber Store::getPrice(Item &item, const CookieNumber &amount, const CookieNumber &amountAlreadyHave) {

    if (amountAlreadyHave == 0)
        return item.baseCost;

    CookieFloater baseCost(item.baseCost);
    CookieFloater itemAmountInInventory(amountAlreadyHave);
    CookieFloater amountToBuy(amount);

    auto amountInInventoryPOW = boost::multiprecision::pow(CookieFloater("1.15"), itemAmountInInventory);
//    std::cerr << "amountPOW: " << (amountInInventoryPOW) << std::endl;

    auto newPrice = baseCost * amountInInventoryPOW;
//    std::cerr << "newPrive: " << newPrice << std::endl;

    auto resultFloat = amountToBuy * newPrice;
//    std::cerr << "resultFLoat: " << resultFloat << std::endl;

    auto result = resultFloat.convert_to<CookieNumber>() + 1; // +1 due to rounding down
//    std::cerr << "result: " << result << std::endl;
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