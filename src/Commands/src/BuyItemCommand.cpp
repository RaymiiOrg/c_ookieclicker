//
// Created by remy on 20-04-20.
//

#include "BuyItemCommand.h"

BuyItemCommand::BuyItemCommand(Item& item, int amount, Inventory& inventory, Wallet &wallet)
: m_Item(item), m_Amount(amount), m_Inventory(inventory), m_Wallet(wallet)
{
}

void BuyItemCommand::execute() {
    int price = m_Item.price * m_Amount;
    auto cps = m_Item.cps * m_Amount;
    if (m_Wallet.getCookieAmount() >= price) {
        m_Inventory.addItem(m_Item, m_Amount);
        m_Wallet.decrementCookieAmount(price);
        m_Wallet.incrementCps(cps);
    }
}

void BuyItemCommand::undo() {
    auto price = m_Item.price * m_Amount;
    auto cps = m_Item.cps * m_Amount;
    m_Inventory.removeItem(m_Item, m_Amount);
    m_Wallet.incrementCookieAmount(price);
    m_Wallet.incrementCps(-cps);
}