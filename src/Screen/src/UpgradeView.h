#ifndef C_OOKIECLIKER_UPGRADEVIEW_H
#define C_OOKIECLIKER_UPGRADEVIEW_H

#include "CpsUpgrade.h"
#include "IInventoryMutator.h"
#include "IItemStoreReader.h"
#include "IWalletMutator.h"
#include "terminalCodes.h"
#include "View.h"
#include "notifyMessage.h"

class UpgradeView : public View
{
    const std::string _name {"Upgrades"};
    IInventoryMutator *inventory = nullptr;
    IWalletMutator *wallet = nullptr;
    notifyMessage *msg = nullptr;
    IItemStoreReader *itemstore = nullptr;
    UpgradeCatalog cpsUpgradeStore;

    void renderCookieTapUpgrades() const;
    void renderCpsUpgrades(const std::string &itemName, const std::string &label) const;

    /** Renders one tier row in the shared bought / next-available / locked
     * style. The bonus wording differs per upgrade kind, so it is passed in
     * pre-formatted: boughtSuffix follows the name on an owned tier,
     * nextSuffix follows the cost on the next purchasable tier. */
    void renderTierRow(const std::string &buyKey, const std::string &tierName,
                       const CookieNumber &cost, const std::string &boughtSuffix,
                       const std::string &nextSuffix, bool bought, bool isNext) const;

public:
    void render() override;
    const std::string &name() override { return _name; };
    void handleInput(const std::string &input) override;
    explicit UpgradeView(IInventoryMutator *inventory, IWalletMutator *wallet, notifyMessage *msg, IItemStoreReader *itemstore)
        : inventory(inventory), wallet(wallet), msg(msg), itemstore(itemstore) {};
};

#endif //C_OOKIECLIKER_UPGRADEVIEW_H
