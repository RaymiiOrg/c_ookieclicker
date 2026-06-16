#ifndef C_OOKIECLIKER_BUYCPSUPGRADECOMMAND_H
#define C_OOKIECLIKER_BUYCPSUPGRADECOMMAND_H

#include "CpsUpgrade.h"
#include "IInventoryMutator.h"
#include "IWalletMutator.h"

class BuyCpsUpgradeCommand
{
public:
    BuyCpsUpgradeCommand(const CpsUpgrade &upgrade,
                         const std::string &itemName,
                         CookieNumber itemBaseCps,
                         IInventoryMutator &inventory,
                         IWalletMutator &wallet);
    void execute();
    void undo();

private:
    const CpsUpgrade m_Upgrade;
    const std::string m_ItemName;
    const CookieNumber m_ItemBaseCps;
    IInventoryMutator &m_Inventory;
    IWalletMutator &m_Wallet;
    CookieNumber m_AddedCps;
};

#endif //C_OOKIECLIKER_BUYCPSUPGRADECOMMAND_H
