//
// Created by remy on 20-04-20.
//

#include "UpdateCookiesCommand.h"

UpdateCookiesCommand::UpdateCookiesCommand(const CookieNumber &amount, Wallet &wallet) :
    m_Amount(amount), m_Wallet(wallet)
{
}

void UpdateCookiesCommand::execute()
{
    m_Wallet.incrementCookieAmount(m_Amount);
}

void UpdateCookiesCommand::undo()
{
    m_Wallet.decrementCookieAmount(m_Amount);
}