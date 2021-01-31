#include "InventoryView.h"

void InventoryView::render()
{
    if (inventory != nullptr)
    {
        if (!inventory->getInventory().empty())
        {
            for (auto &item : inventory->getInventory())
            {
                auto name = item.first;
                auto amount = item.second;
                if (amount > 0)
                {
                    std::cout << name << ": " << cp.print(amount) << std::endl;
                }
            }
        }
        else
        {
            std::cout << "Inventory empty. Get some cookies to buy items." << std::endl;
        }
    }
}

void InventoryView::handleInput(const std::string &input)
{
}
