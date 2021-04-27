#ifndef C_OOKIECLIKER_UPGRADEVIEW_H
#define C_OOKIECLIKER_UPGRADEVIEW_H
#include "Inventory.h"
#include "ItemStore.h"
#include "View.h"

class UpgradeView : public View
{
    const std::string _name {"Upgrades"};
    const Inventory *inventory;
    const ItemStore *store;

public:
    void render() override;
    const std::string &name() override { return _name; };
    void handleInput(const std::string &input) override;
    explicit UpgradeView(const Inventory *inventory, const ItemStore* store) :
        inventory(inventory), store(store) {};
};

#endif //C_OOKIECLIKER_UPGRADEVIEW_H
