#ifndef C_OOKIECLIKER_UpdateCpsCommand_H
#define C_OOKIECLIKER_UpdateCpsCommand_H

#include "Command.h"
#include "Wallet.h"

class UpdateCpsCommand : public Command
{
public:
    UpdateCpsCommand(const CookieNumber &amount, Wallet &wallet);
    void execute() override;
    void undo() override;

private:
    CookieNumber m_Amount;
    Wallet &m_Wallet;
};

#endif //C_OOKIECLIKER_UpdateCpsCommand_H
