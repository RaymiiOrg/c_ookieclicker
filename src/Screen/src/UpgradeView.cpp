#include "UpgradeView.h"

void UpgradeView::render()
{
    if (inventory == nullptr || store == nullptr)
        return;

    if (inventory->getInventory().empty())
    {
        std::cout << "No upgrades available. Get some items first." << std::endl;
        return;
    }
    for (auto &item : inventory->getInventory())
    {
        if (item.amount > 0)
        {
            std::cout << item.itemName << ", level:  " << item.itemLevel << ". Upgrade price: " <<
                store->getUpgradePrice(store->getItemByName(item.itemName), item.itemLevel) <<
                std::endl;
        }
    }
}

void UpgradeView::handleInput(const std::string &input)
{
}
