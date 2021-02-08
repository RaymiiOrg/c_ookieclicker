#include "UpgradeView.h"

void UpgradeView::render()
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
            std::cout << "No upgrades available. Get some items first." << std::endl;
        }
    }
}

void UpgradeView::handleInput(const std::string &input)
{
}
