#ifndef C_OOKIECLIKER_ITEMSTOREVIEW_H
#define C_OOKIECLIKER_ITEMSTOREVIEW_H
#include "Inventory.h"
#include "Item.h"
#include "ItemStore.h"
#include "Globals.h"
#include "ItemStoreShelfView.h"
#include "View.h"
#include "Wallet.h"
#include "notifyMessage.h"
#include "terminalCodes.h"

class ItemStoreView : public View
{
    const std::string _name {"Store"};
    notifyMessage *msg;
    Wallet *wallet;
    Inventory *inventory;
    ItemStore *store;
    ItemStoreShelfView oneItem = ItemStoreShelfView(msg, wallet, inventory, store, 1, "Buy 1");
    ItemStoreShelfView tenItems = ItemStoreShelfView(msg, wallet, inventory, store, 10, "Buy 10");
    ItemStoreShelfView hundredItems = ItemStoreShelfView(msg, wallet, inventory, store, 100, "Buy 100");
    View* activeView = &oneItem;
    std::vector<View *> allviews = {
            dynamic_cast<View *>(&oneItem),
            dynamic_cast<View *>(&tenItems),
            dynamic_cast<View *>(&hundredItems),
    };

public:
    const std::string &name() override { return _name; };
    void render() override;
    void handleInput(const std::string &input) override;
    explicit ItemStoreView(notifyMessage* msg, Wallet* wallet, Inventory* inventory, ItemStore * store) : msg(msg), wallet(wallet), inventory(inventory), store(store) {};

    void listViews() const;
};

#endif //C_OOKIECLIKER_ITEMSTOREVIEW_H
