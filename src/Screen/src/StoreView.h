#ifndef C_OOKIECLIKER_STOREVIEW_H
#define C_OOKIECLIKER_STOREVIEW_H
#include "Store.h"
#include "StoreShelfView.h"
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
    StoreShelfView oneItem = StoreShelfView(msg, wallet, inventory, store, 1, "Buy 1");
    StoreShelfView tenItems = StoreShelfView(msg, wallet, inventory, store, 10, "Buy 10");
    StoreShelfView hundredItems = StoreShelfView(msg, wallet, inventory, store, 100, "Buy 100");
    View* activeView = &oneItem;
    char getCookieInputKey = 'c';
    std::vector<View *> allviews = {
            dynamic_cast<View *>(&oneItem),
            dynamic_cast<View *>(&tenItems),
            dynamic_cast<View *>(&hundredItems),
    };

public:
    const std::string &name() override { return _name; };
    void render() override;
    void handleInput(const std::string &input) override;
    explicit StoreView(notifyMessage* msg, Wallet* wallet, Inventory* inventory,
    Store* store) : msg(msg), wallet(wallet), inventory(inventory), store(store) {};

    void listViews() const;
};

#endif //C_OOKIECLIKER_STOREVIEW_H
