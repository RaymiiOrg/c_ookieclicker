#ifndef C_OOKIECLIKER_AddItemCommand_H
#define C_OOKIECLIKER_AddItemCommand_H

#include "Command.h"
#include "Inventory.h"
#include "ItemStore.h"
#include "Wallet.h"
#include <utility>

class BuyItemCommand : public Command
{
public:
    BuyItemCommand(Item &item, CookieNumber amount, Inventory &inventory, Wallet &wallet, ItemStore &store);
    void execute() override;
    void undo() override;

private:
    Item &m_Item;
    CookieNumber m_Amount;
    Inventory &m_Inventory;
    Wallet &m_Wallet;
    ItemStore &m_ItemStore;
    CookieNumber getPriceOf();

};

#endif //C_OOKIECLIKER_AddItemCommand_H
