//
// Created by remy on 20-04-20.
//

#include "UpdateCpsCommand.h"

UpdateCpsCommand::UpdateCpsCommand(long double amount, Wallet &wallet)
: m_Amount(amount), m_Wallet(wallet)
{
}

void UpdateCpsCommand::execute() {
    m_Wallet.incrementCps(m_Amount);
}

void UpdateCpsCommand::undo() {
    m_Wallet.incrementCps(-m_Amount);
}