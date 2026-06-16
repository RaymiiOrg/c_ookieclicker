#ifndef C_OOKIECLIKER_IWALLETREADER_H
#define C_OOKIECLIKER_IWALLETREADER_H

#include "CookieNumbers.h"

class IWalletReader
{
public:
    virtual ~IWalletReader() = default;
    virtual CookieNumber getCookieAmount() const = 0;
    virtual CookieNumber getCps() const = 0;
    virtual CookieNumber getEffectiveCps() const = 0;
    virtual CookieNumber getCookiesViaInput() const = 0;
    virtual CookieNumber getTotalcookies() const = 0;
    virtual CookieNumber getAchievementBonusMultiplier() const = 0;
};

#endif //C_OOKIECLIKER_IWALLETREADER_H
