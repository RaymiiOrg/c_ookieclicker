#include "UpdateCookiesViaInputCommand.h"

#include <utility>

UpdateCookiesViaInputCommand::UpdateCookiesViaInputCommand(CookieNumber amount, Wallet &wallet) :
        amount(std::move(amount)), m_Wallet(wallet)
{
}

void UpdateCookiesViaInputCommand::execute()
{
    m_Wallet.incrementCookieViaInput(amount);
}

void UpdateCookiesViaInputCommand::undo()
{
    m_Wallet.decrementCookieAmount(amount);
}