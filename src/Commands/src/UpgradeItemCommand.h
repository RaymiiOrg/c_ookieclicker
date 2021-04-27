#ifndef C_OOKIECLIKER_AddItemCommand_H
#define C_OOKIECLIKER_AddItemCommand_H

#include "Command.h"
#include "Inventory.h"
#include "ItemStore.h"
#include "Wallet.h"
#include <utility>

class UpgradeItemCommand : public Command
{
public:
    UpgradeItemCommand(Item &item, Inventory &inventory, Wallet &wallet);
    void execute() override;
    void undo() override;

private:
    Item &m_Item;
    Inventory &m_Inventory;
    Wallet &m_Wallet;
    CookieNumber getPriceOf();

};

#endif //C_OOKIECLIKER_AddItemCommand_H
