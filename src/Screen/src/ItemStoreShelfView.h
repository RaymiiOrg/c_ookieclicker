#ifndef C_OOKIECLIKER_StoreShelfView_H
#define C_OOKIECLIKER_StoreShelfView_H
#include "IInventoryMutator.h"
#include "IItemStoreReader.h"
#include "IWalletMutator.h"
#include "Item.h"
#include "View.h"
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
    IWalletMutator *wallet;
    IInventoryMutator *inventory;
    IItemStoreReader *itemstore;
    int itemQuantity;
    const std::string _name {"StoreShelf"};
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
    explicit ItemStoreShelfView(notifyMessage* msg, IWalletMutator* wallet, IInventoryMutator* inventory, IItemStoreReader* store, int itemQuantity, const std::string &name) : msg(msg), wallet(wallet),
    inventory(inventory), itemstore(store), itemQuantity(itemQuantity), _name(name) {};
    [[nodiscard]] bool isInputRelevant(const std::string &input) const;
    CookieNumber getPriceOfItem(const CookieNumber &itemAmountInInventory, Item &item) const;
};

#endif //C_OOKIECLIKER_StoreShelfView_H
