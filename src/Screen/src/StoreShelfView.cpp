//
// Created by remy on 08-09-20.
//

#include "StoreShelfView.h"
#include "BuyItemCommand.h"

void StoreShelfView::render()
{
    if (wallet && store && inventory && msg) {
        bool enoughMoneyOrHaveItemsAlready = false;
        for (auto &item : store->getStoreInventory()) {
            auto itemAmountInInventory = inventory->getItemCount(item.name);
            CookieNumber priceOfItem = getPriceOfItem(itemAmountInInventory, item);
            if (itemAmountInInventory > 0 && wallet->getCookieAmount() < priceOfItem) {
                enoughMoneyOrHaveItemsAlready = true;
                renderNotEnoughMoneyButDoHaveItemsInInventoryOutput(item, itemAmountInInventory);
            } else if (wallet->getCookieAmount() > priceOfItem) {
                enoughMoneyOrHaveItemsAlready = true;
                renderCanBuy(item, itemAmountInInventory, priceOfItem);
            }
        }
        if (!enoughMoneyOrHaveItemsAlready) {
            std::cout << "Not enough cookies to buy items. Get some cookies!" << std::endl;
        }
    }
}

CookieNumber StoreShelfView::getPriceOfItem(const CookieNumber &itemAmountInInventory, Item &item) const {
    switch (itemQuantity) {
        case 1:
            return Store::getPrice(item, itemAmountInInventory);
        case 10:
            return Store::getPriceOfTen(item, itemAmountInInventory);
        case 100:
            return Store::getPriceOfHundred(item, itemAmountInInventory);
    }
    return CookieNumber(1);
}

void StoreShelfView::renderNotEnoughMoneyButDoHaveItemsInInventoryOutput(Item &item,
                                                                         const CookieNumber &itemAmountInInventory) const {
    std::cout << escapeCode.terminalDim;
    std::cout << "[" << item.buyKey << "]: not enough cookies for " << item.name;
    if (itemQuantity > 1) std::cout << "s";
    std::cout << " (cost: ";
    std::cout << cp.print(Store::getPrice(item, itemAmountInInventory));
    std::cout << " cookies);";
    std::cout << escapeCode.terminalReset;
    std::cout << std::endl;
}


void StoreShelfView::handleInput(const std::string &input)
{
    if (wallet && store && inventory && msg) {
        if (isInputRelevant(input)) {
            for (Item &item : store->getStoreInventory()) {
                if (input == item.buyKey) {
                    if(canPayForItem(item)) {
                        buyItem(CookieNumber(itemQuantity), item);
                        return;
                    } else {
                        msg->setLastItemFailedToBuy(item.name);
                        msg->setCurrentMessage(notifyMessage::msgType::NOT_ENOUGH_MONEY_FOR_ITEM);
                        return;
                    }
                }
            }
        }
    }
}

bool StoreShelfView::isInputRelevant(const std::string &input) const {
    bool isABuyItemKey = false;
    for (const auto& item : store->getStoreInventory()) {
        if (input == item.buyKey) {
            isABuyItemKey = true;
        }
    }
    return isABuyItemKey;
}

void StoreShelfView::buyItem(const CookieNumber &amountToBuy, Item &item)
{
    if (canPayForItem(item) && amountToBuy > CookieNumber(0))
    {
        auto buyCommand = std::make_unique<BuyItemCommand>(item, amountToBuy, *inventory, *wallet, *store);
        buyCommand->execute();
        msg->setLastItemBoughtName(item.name);
        msg->setLastItemBoughtAmount(amountToBuy);
        msg->setCurrentMessage(notifyMessage::msgType::BOUGHT_ITEM);
    }
    else
    {
        msg->setLastItemFailedToBuy(item.name);
        msg->setCurrentMessage(notifyMessage::msgType::NOT_ENOUGH_MONEY_FOR_ITEM);
    }
}

bool StoreShelfView::canPayForItem(Item &item)
{
    if (itemQuantity == 100 && canBuyHundred(item))
        return true;
    if (itemQuantity == 10 && canBuyTen(item))
        return true;

    return canBuyOne(item);
}

bool StoreShelfView::canBuyOne(Item &item)
{
    auto itemCount = inventory->getItemCount(item.name);
    return wallet->getCookieAmount() >= Store::getPrice(item, itemCount);
}

bool StoreShelfView::canBuyTen(Item &item)
{
    if (!canBuyOne(item))
        return false;
    auto itemCount = inventory->getItemCount(item.name);
    if (Store::getPriceOfTen(item, itemCount) > wallet->getCookieAmount())
        return false;
    return true;
}

bool StoreShelfView::canBuyHundred(Item &item)
{
    if (!canBuyTen(item))
        return false;
    auto itemCount = inventory->getItemCount(item.name);
    if (Store::getPriceOfHundred(item, itemCount) > wallet->getCookieAmount())
        return false;
    return true;
}

void StoreShelfView::renderCanBuy(Item &item, const CookieNumber &itemAmountInInventory, const CookieNumber & price) const {
    CookieNumber cpsOfX = item.cps * CookieNumber(itemQuantity);
    std::cout << "[" << item.buyKey << "]"
              << ": buy " << itemQuantity << " " << item.name;
    if (itemQuantity != 1) std::cout << "s";
    std::cout << "; cost: "
              << cp.print(price) << " cookies; +"
              << cp.print(cpsOfX) << " cps; ";
    std::cout << std::endl;
}



