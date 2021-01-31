#ifndef C_OOKIECLIKER_StoreShelfView_H
#define C_OOKIECLIKER_StoreShelfView_H
#include "Store.h"
#include "notifyMessage.h"
#include "Wallet.h"
#include "Item.h"
#include "Inventory.h"
#include "terminalCodes.h"
#include "View.h"

#include <utility>
#include <functional>

/** A store shelf contains a certain set of items. 
 * In our case, it shows options to buy One, Ten or 
 * Hundred of each item.
 */
class StoreShelfView : public View
{
    const std::string _name {"StoreShelf"};
    notifyMessage *msg;
    Wallet *wallet;
    Inventory *inventory;
    Store *store;
    int itemQuantity;
    bool canPayForItem(Item &item);
    void buyItem(const CookieNumber &amountToBuy, Item &item);
    void renderCanBuy(Item &item, const CookieNumber &itemAmountInInventory,
                      const CookieNumber & price) const;
    void renderNotEnoughMoneyButDoHaveItemsInInventoryOutput(Item &item,
                                                             const CookieNumber &itemAmountInInventory)
                                                             const;

public:
    const std::string &name() override { return _name; };
    void render() override;
    void handleInput(const std::string &input) override;
    explicit StoreShelfView(notifyMessage* msg, Wallet* wallet, Inventory* inventory,
    Store* store, int itemQuantity, std::string  name) : msg(msg), wallet(wallet),
    inventory(inventory), store(store), itemQuantity(itemQuantity), _name(std::move(name)) {};
    [[nodiscard]] bool isInputRelevant(const std::string &input) const;
    CookieNumber getPriceOfItem(const CookieNumber &itemAmountInInventory, Item &item) const;
};

#endif //C_OOKIECLIKER_StoreShelfView_H
