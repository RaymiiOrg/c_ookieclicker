//
// Created by remy on 20-04-20.
//

#ifndef C_OOKIECLIKER_AddItemCommand_H
#define C_OOKIECLIKER_AddItemCommand_H

#include "Command.h"
#include "Wallet.h"
#include "Inventory.h"
#include "Store.h"
#include <utility>

class BuyItemCommand : public Command {
public:
    BuyItemCommand(Item& itemName, CookieNumber amount, Inventory& inventory, Wallet &wallet, Store &store);
    void execute() override;
    void undo() override;

private:
    Inventory &m_Inventory;
    Wallet &m_Wallet;
    CookieNumber m_Amount;
    Store& m_Store;
    Item& m_Item;

};


#endif //C_OOKIECLIKER_AddItemCommand_H
