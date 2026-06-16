#ifndef C_OOKIECLIKER_CPSUPGRADE_H
#define C_OOKIECLIKER_CPSUPGRADE_H

#include "CookieNumbers.h"
#include <string>
#include <vector>

struct CpsUpgrade {
    std::string name;
    CookieNumber cost;
    CookieNumber boostPercent;
};

struct ItemCpsUpgrades {
    std::string targetItemName;
    std::string buyKey;
    std::vector<CpsUpgrade> tiers;
};

class UpgradeCatalog {
    std::vector<ItemCpsUpgrades> _upgrades;
public:
    UpgradeCatalog();
    const std::vector<ItemCpsUpgrades> &getUpgrades() const { return _upgrades; }
    const ItemCpsUpgrades *getUpgradesForItem(const std::string &itemName) const;
};

#endif //C_OOKIECLIKER_CPSUPGRADE_H
