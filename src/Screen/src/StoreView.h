//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_STOREVIEW_H
#define C_OOKIECLIKER_STOREVIEW_H
#include "Store.h"
#include "notifyMessage.h"
#include "Wallet.h"
#include "Item.h"
#include "Inventory.h"
#include "terminalCodes.h"
#include "View.h"

class StoreView : public View
{
    const std::string _name {"Store"};
    notifyMessage *msg;
    Wallet *wallet;
    Inventory *inventory;
    Store *store;

public:
    const std::string &name() override { return _name; };
    void render() override;
    void handleInput(const std::string &input) override;
    explicit StoreView(notifyMessage* msg, Wallet* wallet, Inventory* inventory,
    Store* store) : msg(msg), wallet(wallet), inventory(inventory), store(store) {};

    bool canPayForItem(const CookieNumber &amountToBuy, Item &item);

    void buyItem(const CookieNumber &amountToBuy, Item &item);

    bool canBuyOne(Item &item);

    bool canBuyTen(Item &item);

    bool canBuyHundred(Item &item);

    int canBuyTenOrHundred(Item &item);

    int maxItemAmount(Item &item);

    void handleBuyItemChoice(const std::string &input);
};

#endif //C_OOKIECLIKER_STOREVIEW_H
