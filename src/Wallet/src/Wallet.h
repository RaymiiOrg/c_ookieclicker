//
// Created by remy on 21-04-20.
//

#ifndef C_OOKIECLIKER_WALLET_H
#define C_OOKIECLIKER_WALLET_H
#include "CookieNumbers.h"

class Wallet {
    public:
    const CookieNumber getCookieAmount();
    const CookieNumber getCps();
    void incrementCookieAmount(CookieNumber amount);
    void decrementCookieAmount(CookieNumber amount);
    void incrementCps(CookieNumber amount);
    void decrementCps(CookieNumber amount);
    const CookieNumber getTotalcookies();
    void reset();
private:
    CookieNumber _cps = 0;
    CookieNumber _cookieAmount = 0;
    CookieNumber _totalcookies = 0;

    void setCps(const CookieNumber &cps);
    void setCookieAmount(const CookieNumber &cookieAmount);
    void setTotalcookies(const CookieNumber &totalcookies);

private:
    friend class Save;


};


#endif
