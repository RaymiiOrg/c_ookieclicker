//
// Created by remy on 20-04-20.
//

#include "Inventory.h"


void Inventory::addItem(const Item& item, unsigned int amountToAdd) {
    if ( m_Inventory.find(item) != m_Inventory.end() ) {
        m_Inventory.at(item) += amountToAdd;
    }
    else
    {
        m_Inventory.insert(std::pair<Item, unsigned int>(item, amountToAdd));
    }
}

void Inventory::removeItem(const Item &item, unsigned int amountToRemove) {
    if ( m_Inventory.find(item) != m_Inventory.end() ) {
        if (m_Inventory.at(item) >= amountToRemove) {
            m_Inventory.at(item) -= amountToRemove;
        } else {
            m_Inventory.erase(item);
        }
    }
}

unsigned int Inventory::getItemCount(const Item &item) {
    if ( m_Inventory.find(item) != m_Inventory.end() ) {
        return m_Inventory.at(item);
    } else {
        return 0;
    }
}

void Inventory::printInventory() {
    if (!m_Inventory.empty()) {
        for (const auto &item : m_Inventory) {
            std::cout << std::setprecision(1) << std::fixed <<
                      "Item: " << item.first.name << "; price: " << item.first.price <<
                      "; cps: " << item.first.cps << "; Amount: " << item.second << "\n";
        }
    } else {
        std::cout << "Inventory empty\n";
    }
}