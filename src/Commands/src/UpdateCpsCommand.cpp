//
// Created by remy on 20-04-20.
//

#include "UpdateCpsCommand.h"

UpdateCpsCommand::UpdateCpsCommand(const CookieNumber& amount, Wallet &wallet)
: m_Amount(amount), m_Wallet(wallet)
{
}

void UpdateCpsCommand::execute() {
    m_Wallet.incrementCps(m_Amount);
}

void UpdateCpsCommand::undo() {
    m_Wallet.decrementCps(m_Amount);
}