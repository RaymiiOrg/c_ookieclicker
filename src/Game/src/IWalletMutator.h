#ifndef C_OOKIECLIKER_IWALLETMUTATOR_H
#define C_OOKIECLIKER_IWALLETMUTATOR_H

#include "CookieNumbers.h"

class IWalletMutator
{
public:
    virtual ~IWalletMutator() = default;
    virtual CookieNumber getCookieAmount() const = 0;
    virtual void incrementCookieAmount(const CookieNumber &amount) = 0;
    virtual void decrementCookieAmount(const CookieNumber &amount) = 0;
    virtual void incrementCps(const CookieNumber &amount) = 0;
    virtual void decrementCps(const CookieNumber &amount) = 0;
    virtual void incrementCookieViaInput(const CookieNumber &amount) = 0;
};

#endif //C_OOKIECLIKER_IWALLETMUTATOR_H
