//
// Created by remy on 08-09-20.
//

#include "StoreView.h"
#include "BuyItemCommand.h"

void StoreView::render()
{
    if (wallet && store && inventory && msg) {
        bool oneItem = true;
        bool enoughMoneyOrHaveItemsAlready = false;
        for (auto &item : store->getStoreInventory()) {
            auto itemCount = inventory->getItemCount(item.name);
            if (!canPayForItem(1, item) && itemCount > 0) {
                enoughMoneyOrHaveItemsAlready = true;
                std::cout << escapeCode.terminalDim;
                std::cout << "[" << item.buyOneCursor << "]: not enough cookies for " << item.name << " (cost: ";
                std::cout << cp.print(Store::getPrice(item, itemCount));
                std::cout << " cookies);";
                std::cout << escapeCode.terminalReset << "\n";
            } else if (canPayForItem(1, item)) {
                enoughMoneyOrHaveItemsAlready = true;
                if (oneItem) {
                    std::cout << "[" << item.buyOneCursor << "]"
                              << ": buy " << item.name << "; cost: ";
                    std::cout << cp.print(Store::getPrice(item, itemCount));
                    std::cout << " cookies; +";
                    std::cout << cp.print(item.cps);
                    std::cout << " cps; ";
                } else {
                    int maxbuy = canBuyTenOrHundred(item);
                    if (maxbuy == 10) {
                        CookieNumber cpsOfTen = item.cps * CookieNumber(maxbuy);
                        std::cout << "[" << item.buyMaxCursor << "]"
                                  << ": buy 10 " << item.name << "s; cost: "
                                  << cp.print(Store::getPriceOfTen(item, itemCount)) << " cookies; +"
                                  << cp.print(cpsOfTen) << " cps; ";
                    } else if (maxbuy == 100) {
                        CookieNumber cpsOfHundred = item.cps * CookieNumber(maxbuy);
                        std::cout << "[" << item.buyMaxCursor << "]"
                                  << ": buy 100 " << item.name << "s; cost: "
                                  << cp.print(Store::getPriceOfHundred(item, itemCount)) << " cookies +"
                                  << cp.print(cpsOfHundred) << " cps; ";
                    } else {
                        std::cout << escapeCode.terminalDim;
                        std::cout << "[" << item.buyMaxCursor << "]: not enough cookies for 10 " << item.name
                                  << "s (cost: ";
                        std::cout << cp.print(Store::getPriceOfTen(item, itemCount));
                        std::cout << " cookies);";
                        std::cout << escapeCode.terminalReset;
                    }
                }
                std::cout << escapeCode.terminalReset << "\n";
            }
        }
        if (!enoughMoneyOrHaveItemsAlready) {
            std::cout << "No items available, get some more cookies.\n";
        }
    } else {
        std::cout << "Loading " << _name << "..." << std::endl;
    }
}

void StoreView::handleInput(const std::string &input)
{
    if (wallet && store && inventory && msg) {
        for (Item &item : store->getStoreInventory()) {
            if (input == item.buyOneCursor && canPayForItem(1, item)) {
                buyItem(CookieNumber(1), item);
            } else if (input == item.buyMaxCursor) {
                int maxbuy = canBuyTenOrHundred(item);
                if ((maxbuy == 10 && canPayForItem(10, item)) or (maxbuy == 100 && canPayForItem(100, item))) {
                    buyItem(CookieNumber(maxbuy), item);
                } else {
                    msg->setLastItemFailedToBuy(item.name);
                    msg->setCurrentMessage(notifyMessage::msgType::NOT_ENOUGH_MONEY_FOR_ITEM);
                }
            }
        }
    }
}


void StoreView::buyItem(const CookieNumber &amountToBuy, Item &item)
{
    if (canPayForItem(amountToBuy, item) && amountToBuy > CookieNumber(0))
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

bool StoreView::canPayForItem(const CookieNumber &amountToBuy, Item &item)
{
    if (amountToBuy == CookieNumber(100) && canBuyHundred(item))
        return true;
    if (amountToBuy == CookieNumber(10) && canBuyTen(item))
        return true;

    return canBuyOne(item);
}


bool StoreView::canBuyOne(Item &item)
{
    auto itemCount = inventory->getItemCount(item.name);
    return wallet->getCookieAmount() >= Store::getPrice(item, itemCount);
}

bool StoreView::canBuyTen(Item &item)
{
    if (!canBuyOne(item))
        return false;
    auto itemCount = inventory->getItemCount(item.name);
    if (Store::getPriceOfTen(item, itemCount) > wallet->getCookieAmount())
        return false;
    return true;
}

bool StoreView::canBuyHundred(Item &item)
{
    if (!canBuyTen(item))
        return false;
    auto itemCount = inventory->getItemCount(item.name);
    if (Store::getPriceOfHundred(item, itemCount) > wallet->getCookieAmount())
        return false;
    return true;
}

int StoreView::canBuyTenOrHundred(Item &item)
{
    int maxbuy = 0;
    if (canBuyTen(item))
    {
        maxbuy = 10;
        if (canBuyHundred(item))
        {
            maxbuy = 100;
        }
    }
    return maxbuy;
}

int StoreView::maxItemAmount(Item &item)
{
    CookieNumber priceOfX;
    for (int i = 0; i < 101; ++i)
    {
        priceOfX += Store::getPrice(item, inventory->getItemCount(item.name) + i);
        if (priceOfX > wallet->getCookieAmount())
            return i;
    }
    return 0;
}



void StoreView::handleBuyItemChoice(const std::string &input)
{

}


