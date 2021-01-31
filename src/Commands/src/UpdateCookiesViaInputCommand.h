#ifndef C_OOKIECLIKER_UpdateCookiesCommand_H
#define C_OOKIECLIKER_UpdateCookiesCommand_H
#include "Command.h"
#include "Wallet.h"

class UpdateCookiesViaInputCommand : public Command
{
public:
    UpdateCookiesViaInputCommand(CookieNumber amount, Wallet &wallet);
    void execute() override;
    void undo() override;

private:
    Wallet &m_Wallet;
    CookieNumber amount;
};

#endif //C_OOKIECLIKER_UpdateCookiesCommand_H
