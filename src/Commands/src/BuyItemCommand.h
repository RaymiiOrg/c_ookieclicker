#ifndef C_OOKIECLIKER_AddItemCommand_H
#define C_OOKIECLIKER_AddItemCommand_H

#include "Command.h"
#include "IInventoryMutator.h"
#include "IItemStoreReader.h"
#include "IWalletMutator.h"
#include <utility>

class BuyItemCommand : public Command
{
public:
    BuyItemCommand(Item &item, CookieNumber amount, IInventoryMutator &inventory, IWalletMutator &wallet, IItemStoreReader &store);
    virtual ~BuyItemCommand() =default;

    void execute() override;
    void undo() override;

private:
    Item &m_Item;
    CookieNumber m_Amount;
    IInventoryMutator &m_Inventory;
    IWalletMutator &m_Wallet;
    IItemStoreReader &m_ItemStore;
    CookieNumber getPriceOf();

    // State captured at execute() so undo() reverses exactly what was applied,
    // independent of any inventory/multiplier/price changes made afterwards.
    bool m_Executed{false};
    CookieNumber m_PaidPrice{0};
    CookieNumber m_AddedCps{0};
    CookieNumber m_AddedCookiesPerTap{0};

};

#endif //C_OOKIECLIKER_AddItemCommand_H
