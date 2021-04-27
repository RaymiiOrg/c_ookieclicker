#ifndef C_OOKIECLIKER_StoreShelfView_H
#define C_OOKIECLIKER_StoreShelfView_H
#include "Inventory.h"
#include "Item.h"
#include "ItemStore.h"
#include "View.h"
#include "Wallet.h"
#include "notifyMessage.h"
#include "terminalCodes.h"

#include <utility>
#include <functional>

/** A store shelf contains a certain set of items. 
 * In our case, it shows options to buy One, Ten or 
 * Hundred of each item.
 */
class ItemStoreShelfView : public View
{
    notifyMessage *msg;
    Wallet *wallet;
    Inventory *inventory;
    ItemStore *itemstore;
    int itemQuantity;
    const std::string _name {"StoreShelf"};
    bool canPayForItem(const Item &item);
    void buyItem(const CookieNumber &amountToBuy, const Item &item);
    void renderCanBuy(const Item &item, const CookieNumber &itemAmountInInventory,
                      const CookieNumber & price) const;
    void renderNotEnoughMoneyButDoHaveItemsInInventoryOutput(const Item &item,
                                                             const CookieNumber &itemAmountInInventory)
                                                             const;

public:
    const std::string &name() override { return _name; };
    void render() override;
    void handleInput(const std::string &input) override;
    explicit ItemStoreShelfView(notifyMessage* msg, Wallet* wallet, Inventory* inventory, ItemStore * store, int itemQuantity, std::string  name) : msg(msg), wallet(wallet),
    inventory(inventory), itemstore(store), itemQuantity(itemQuantity), _name(std::move(name)) {};
    [[nodiscard]] bool isInputRelevant(const std::string &input) const;
    CookieNumber getPriceOfItem(const CookieNumber &itemAmountInInventory, const Item &item) const;
};

#endif //C_OOKIECLIKER_StoreShelfView_H
