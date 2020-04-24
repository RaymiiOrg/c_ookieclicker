//
// Created by remy on 20-04-20.
//

#ifndef C_OOKIECLIKER_UpdateCookiesCommand_H
#define C_OOKIECLIKER_UpdateCookiesCommand_H
#include "Command.h"
#include "Wallet.h"

class UpdateCookiesCommand : public Command {
public:
    UpdateCookiesCommand(long double amount, Wallet& wallet);
    void execute() override;
    void undo() override;

private:
    Wallet &m_Wallet;
    long double m_Amount = 0;
};


#endif //C_OOKIECLIKER_UpdateCookiesCommand_H
