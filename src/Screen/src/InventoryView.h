#ifndef C_OOKIECLIKER_INVENTORYVIEW_H
#define C_OOKIECLIKER_INVENTORYVIEW_H
#include "Inventory.h"
#include "View.h"

class InventoryView : public View
{
    const std::string _name {"Inventory"};
    const Inventory *inventory;

public:
    void render() override;
    const std::string &name() override { return _name; };
    void handleInput(const std::string &input) override;
    explicit InventoryView(const Inventory *inventory) :
        inventory(inventory) {};
};

#endif //C_OOKIECLIKER_INVENTORYVIEW_H
