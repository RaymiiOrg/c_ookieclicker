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
    BuyItemCommand(Item& item, CookieNumber amount, Inventory& inventory, Wallet &wallet, Store &store);
    void execute() override;
    void undo() override;

private:
    Inventory &m_Inventory;
    Wallet &m_Wallet;
    CookieNumber m_Amount;
    Item& m_Item;
    Store& m_Store;

};


#endif //C_OOKIECLIKER_AddItemCommand_H
