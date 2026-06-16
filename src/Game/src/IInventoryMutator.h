#ifndef C_OOKIECLIKER_IINVENTORYMUTATOR_H
#define C_OOKIECLIKER_IINVENTORYMUTATOR_H

#include "CookieNumbers.h"
#include <string>

class IInventoryMutator
{
public:
    virtual ~IInventoryMutator() = default;
    virtual CookieNumber getItemCount(const std::string &itemName) const = 0;
    virtual void addItem(const std::string &item, const CookieNumber &amountToAdd) = 0;
    virtual void removeItem(const std::string &item, const CookieNumber &amountToRemove) = 0;
    virtual void incrementCookiesPerTap(const CookieNumber &amount) = 0;
    virtual void decrementCookiesPerTap(const CookieNumber &amount) = 0;
    virtual CookieNumber getCpsMultiplier(const std::string &itemName) const = 0;
    virtual void applyCpsBoost(const std::string &itemName, const CookieNumber &boostPercent) = 0;
    virtual void revertCpsBoost(const std::string &itemName, const CookieNumber &boostPercent) = 0;
    virtual size_t getCpsUpgradeTierCount(const std::string &itemName) const = 0;
    virtual void incrementCpsUpgradeTier(const std::string &itemName) = 0;
    virtual void decrementCpsUpgradeTier(const std::string &itemName) = 0;
};

#endif //C_OOKIECLIKER_IINVENTORYMUTATOR_H
