#include "ItemStoreShelfView.h"
#include "BuyItemCommand.h"

void ItemStoreShelfView::render()
{
    if (wallet && itemstore && inventory && msg)
    {
        bool enoughMoneyOrHaveItemsAlready = false;
        for (auto &item : itemstore->getStoreInventory())
        {
            auto itemAmountInInventory = inventory->getItemCount(item.name);
            CookieNumber priceOfItem = getPriceOfItem(itemAmountInInventory, item);
            if (priceOfItem == 0)
                continue;

            if (itemAmountInInventory > 0 && wallet->getCookieAmount() < priceOfItem)
            {
                enoughMoneyOrHaveItemsAlready = true;
                renderNotEnoughMoneyButDoHaveItemsInInventoryOutput(item, itemAmountInInventory);
            }
            else if (wallet->getCookieAmount() > priceOfItem)
            {
                enoughMoneyOrHaveItemsAlready = true;
                renderCanBuy(item, itemAmountInInventory, priceOfItem);
            }
        }
        if (!enoughMoneyOrHaveItemsAlready)
        {
            std::cout << "Not enough cookies to buy items. Get some cookies!" << std::endl;
        }
    }
}

CookieNumber ItemStoreShelfView::getPriceOfItem(const CookieNumber &itemAmountInInventory, Item &item) const
{
    return itemstore->priceOf(item, itemAmountInInventory, itemQuantity);
}

void ItemStoreShelfView::renderNotEnoughMoneyButDoHaveItemsInInventoryOutput(Item &item, const CookieNumber &itemAmountInInventory) const
{
    std::string displayName = item.getDisplayName(itemAmountInInventory);
    std::cout << escapeCode.terminalDim;
    std::cout << "[" << item.buyKey << "]: not enough cookies for ";
    if (item.tiers.empty()) {
        std::cout << std::to_string(itemQuantity) << " " << displayName;
        if (itemQuantity > 1) std::cout << "s";
    } else {
        std::cout << displayName;
    }
    std::cout << " (cost: ";
    std::cout << cp.print(itemstore->priceOf(item, itemAmountInInventory, itemQuantity));
    std::cout << " cookies);";
    std::cout << escapeCode.terminalReset;
    std::cout << std::endl;
}

void ItemStoreShelfView::handleInput(const std::string &input)
{
    if (wallet && itemstore && inventory && msg)
    {
        if (isInputRelevant(input))
        {
            for (Item &item : itemstore->getStoreInventory())
            {
                if (input == item.buyKey)
                {
                    if (canPayForItem(item))
                    {
                        buyItem(CookieNumber(itemQuantity), item);
                        return;
                    }
                    else
                    {
                        msg->setLastItemFailedToBuy(item.name);
                        msg->setCurrentMessage(notifyMessage::msgType::NOT_ENOUGH_MONEY_FOR_ITEM);
                        return;
                    }
                }
            }
        }
    }
}

bool ItemStoreShelfView::isInputRelevant(const std::string &input) const
{
    bool isABuyItemKey = false;
    for (const auto &item : itemstore->getStoreInventory())
    {
        if (input == item.buyKey)
        {
            isABuyItemKey = true;
        }
    }
    return isABuyItemKey;
}

void ItemStoreShelfView::buyItem(const CookieNumber &amountToBuy, Item &item)
{
    if (canPayForItem(item) && amountToBuy > CookieNumber(0))
    {
        if (!item.tiers.empty()) {
            CookieNumber tierIdx = inventory->getItemCount(item.name);
            auto buyCommand = std::make_unique<BuyItemCommand>(item, amountToBuy, *inventory, *wallet, *itemstore);
            buyCommand->execute();
            msg->setLastItemBoughtName(item.getDisplayName(tierIdx));
            msg->setLastItemBoughtAmount(item.getTierBonus(tierIdx));
            msg->setCurrentMessage(notifyMessage::msgType::BOUGHT_TAP_UPGRADE);
        } else {
            auto buyCommand = std::make_unique<BuyItemCommand>(item, amountToBuy, *inventory, *wallet, *itemstore);
            buyCommand->execute();
            msg->setLastItemBoughtName(item.name);
            msg->setLastItemBoughtAmount(amountToBuy);
            msg->setCurrentMessage(notifyMessage::msgType::BOUGHT_ITEM);
        }
    }
    else
    {
        msg->setLastItemFailedToBuy(item.name);
        msg->setCurrentMessage(notifyMessage::msgType::NOT_ENOUGH_MONEY_FOR_ITEM);
    }
}

bool ItemStoreShelfView::canPayForItem(Item &item)
{
    auto itemCount = inventory->getItemCount(item.name);
    return wallet->getCookieAmount() >= itemstore->priceOf(item, itemCount, itemQuantity);
}

void ItemStoreShelfView::renderCanBuy(Item &item, const CookieNumber &itemAmountInInventory, const CookieNumber &price) const
{
    std::string displayName = item.getDisplayName(itemAmountInInventory);
    std::cout << "[" << item.buyKey << "]";
    if (!item.tiers.empty()) {
        CookieNumber bonus = item.getTierBonus(itemAmountInInventory);
        std::string noun = (bonus == CookieNumber(1)) ? "cookie" : "cookies";
        std::cout << ": upgrade to " << displayName
                  << "; cost: " << cp.print(price) << " cookies"
                  << "; +" << cp.print(bonus) << " " << noun << " per tap";
    } else {
        std::cout << ": buy " << itemQuantity << " " << displayName;
        if (itemQuantity != 1)
            std::cout << "s";
        std::cout << "; cost: " << cp.print(price) << " cookies; +";
        if (item.cookiesPerTap > CookieNumber(0))
            std::cout << cp.print(item.cookiesPerTap * CookieNumber(itemQuantity)) << " cookies per tap";
        else
            std::cout << cp.print(item.cpsGain(CookieNumber(itemQuantity), inventory->getCpsMultiplier(item.name))) << " cps";
    }
    std::cout << "; " << std::endl;
}
