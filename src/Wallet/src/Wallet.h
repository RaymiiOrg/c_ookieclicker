//
// Created by remy on 21-04-20.
//

#ifndef C_OOKIECLIKER_WALLET_H
#define C_OOKIECLIKER_WALLET_H
#include "CookieNumbers.h"
#include "Subject.h"

class Wallet : public Subject
{
public:
    CookieNumber getCookieAmount() const;
    CookieNumber getCps() const;
    void incrementCookieAmount(const CookieNumber &amount);
    void decrementCookieAmount(const CookieNumber &amount);
    void incrementCps(const CookieNumber &amount);
    void decrementCps(const CookieNumber &amount);
    CookieNumber getTotalcookies();
    void reset();

private:
    CookieNumber _cps = 0;
    CookieNumber _cookieAmount = 0;
    CookieNumber _totalcookies = 0;
    void setCps(const CookieNumber &cps);
    void setCookieAmount(const CookieNumber &cookieAmount);
    void setTotalcookies(const CookieNumber &totalcookies);
    friend class Save;
};

#endif
