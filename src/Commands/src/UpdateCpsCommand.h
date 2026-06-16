#ifndef C_OOKIECLIKER_UpdateCpsCommand_H
#define C_OOKIECLIKER_UpdateCpsCommand_H

#include "Command.h"
#include "IWalletMutator.h"

class UpdateCpsCommand : public Command
{
public:
    UpdateCpsCommand(const CookieNumber &amount, IWalletMutator &wallet);
    virtual ~UpdateCpsCommand() =default;
    void execute() override;
    void undo() override;

private:
    CookieNumber m_Amount;
    IWalletMutator &m_Wallet;
};

#endif //C_OOKIECLIKER_UpdateCpsCommand_H
