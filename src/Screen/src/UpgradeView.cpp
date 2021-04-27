#include "UpgradeView.h"

void UpgradeView::render()
{
    std::cout << std::endl; // renderInputBar();
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
            auto itemUpgradePrice = ItemStore::getUpgradePrice(store->getItemByName(item.itemName), item.itemLevel);
            std::cout << "[" << item.itemName << "]: current level:  " << item.itemLevel << ". Upgrade price: " <<
                cp.print(itemUpgradePrice) <<
                std::endl;
        }
    }
}

void UpgradeView::handleInput(const std::string &input)
{
}
