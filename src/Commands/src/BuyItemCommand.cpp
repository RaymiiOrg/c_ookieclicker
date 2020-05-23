//
// Created by remy on 20-04-20.
//

#include "BuyItemCommand.h"

BuyItemCommand::BuyItemCommand(Item& item, CookieNumber  amount, Inventory& inventory, Wallet &wallet, Store &store)
: m_Item(item), m_Amount(std::move(amount)), m_Inventory(inventory), m_Wallet(wallet), m_Store(store)
{
}

void BuyItemCommand::execute() {
    CookieNumber price = m_Item.price * m_Amount;
    auto cps = m_Item.cps * m_Amount;
    if (m_Wallet.getCookieAmount() >= price) {
        m_Inventory.addItem(m_Item, m_Amount);
        m_Wallet.decrementCookieAmount(price);
        m_Wallet.incrementCps(cps);
        boost::multiprecision::cpp_dec_float_100 itemPrice(m_Item.price);
        auto increaseAmount = ((m_Item.percentIncreaseWhenBought / 100) * itemPrice);
        m_Item.price += (increaseAmount.convert_to<CookieNumber>() * m_Amount);
    }
}

void BuyItemCommand::undo() {
    auto price = m_Item.price * m_Amount;
    auto cps = m_Item.cps * m_Amount;
    m_Inventory.removeItem(m_Item, m_Amount);
    m_Wallet.incrementCookieAmount(price);
    m_Wallet.decrementCps(cps);
}