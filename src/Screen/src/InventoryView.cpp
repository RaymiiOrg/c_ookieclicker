#include "InventoryView.h"

void InventoryView::render()
{
    std::cout << std::endl;
    if (inventory == nullptr)
        return;

    if (inventory->getInventory().empty())
    {
        std::cout << "Inventory empty. Get some cookies to buy items." << std::endl;
        return;
    }

    for (auto &item : inventory->getInventory())
    {
        if (item.amount > 0)
        {
            std::cout << item.itemName << ": " << cp.print(item.amount) << "; Lvl: "
                      << item.itemLevel << std::endl;
        }
    }
}

void InventoryView::handleInput(const std::string &input)
{
}
