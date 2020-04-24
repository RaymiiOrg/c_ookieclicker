//
// Created by remy on 20-04-20.
//

#ifndef C_OOKIECLIKER_UpdateCpsCommand_H
#define C_OOKIECLIKER_UpdateCpsCommand_H

#include "Command.h"
#include "Game.h"

class UpdateCpsCommand : public Command {
public:
    UpdateCpsCommand(long double amount, Wallet &wallet);
    void execute() override;
    void undo() override;

private:
    Wallet &m_Wallet;
    long double m_Amount = 0;
};


#endif //C_OOKIECLIKER_UpdateCpsCommand_H
