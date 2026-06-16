#ifndef C_OOKIECLIKER_UpdateCookiesCommand_H
#define C_OOKIECLIKER_UpdateCookiesCommand_H
#include "Command.h"
#include "IWalletMutator.h"

class UpdateCookiesViaInputCommand : public Command
{
public:
    UpdateCookiesViaInputCommand(CookieNumber amount, IWalletMutator &wallet);
    virtual ~UpdateCookiesViaInputCommand() =default;
    void execute() override;
    void undo() override;

private:
    CookieNumber amount;
    IWalletMutator &m_Wallet;
};

#endif //C_OOKIECLIKER_UpdateCookiesCommand_H
