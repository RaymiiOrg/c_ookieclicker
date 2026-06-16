#ifndef C_OOKIECLIKER_INVENTORY_H
#define C_OOKIECLIKER_INVENTORY_H

#include "CookieNumbers.h"
#include "ICookieStats.h"
#include "IInventoryMutator.h"
#include "IInventoryReader.h"
#include "IResettable.h"
#include "Item.h"
#include <iomanip>
#include <iostream>
#include <map>

class Inventory : public ICookieStats, public IInventoryReader, public IInventoryMutator, public IResettable
{
private:
    std::map<std::string, CookieNumber> m_Inventory;
    std::string last_item_added;
    CookieNumber last_item_added_amount;
    CookieNumber _cookiesPerTap = 1;
    std::map<std::string, CookieNumber> _cpsMultipliers;
    std::map<std::string, size_t> _cpsUpgradeTierCounts;

public:
    void addItem(const std::string &, const CookieNumber &amountToAdd) override;
    void removeItem(const std::string &, const CookieNumber &amountToRemove) override;
    void reset() override;
    CookieNumber getItemCount(const std::string &) const override;
    CookieNumber getLastItemAddedAmount();
    CookieNumber getCookiesPerTap() const override;
    void incrementCookiesPerTap(const CookieNumber &amount) override;
    void decrementCookiesPerTap(const CookieNumber &amount) override;
    const std::string &getLastItemAdded();
    const std::map<std::string, CookieNumber> &getInventory() const override { return m_Inventory; };

    CookieNumber getCpsMultiplier(const std::string &itemName) const override;
    void applyCpsBoost(const std::string &itemName, const CookieNumber &boostPercent) override;
    void revertCpsBoost(const std::string &itemName, const CookieNumber &boostPercent) override;
    size_t getCpsUpgradeTierCount(const std::string &itemName) const override;
    void incrementCpsUpgradeTier(const std::string &itemName) override;
    void decrementCpsUpgradeTier(const std::string &itemName) override;

    friend class Save;
};

#endif //C_OOKIECLIKER_INVENTORY_H
