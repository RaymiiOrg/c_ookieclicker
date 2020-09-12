//
// Created by remy on 20-04-20.
//

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
    Wallet &m_Wallet;
    CookieNumber m_Amount;
};

#endif //C_OOKIECLIKER_UpdateCpsCommand_H
