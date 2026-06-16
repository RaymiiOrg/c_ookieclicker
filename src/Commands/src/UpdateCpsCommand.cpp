#include "UpdateCpsCommand.h"

UpdateCpsCommand::UpdateCpsCommand(const CookieNumber &amount, IWalletMutator &wallet) :
    m_Amount(amount), m_Wallet(wallet)
{
}

void UpdateCpsCommand::execute()
{
    m_Wallet.incrementCps(m_Amount);
}

void UpdateCpsCommand::undo()
{
    m_Wallet.decrementCps(m_Amount);
}