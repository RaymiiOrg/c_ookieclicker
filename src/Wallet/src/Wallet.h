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
private:
    CookieNumber cps = 0;
    CookieNumber cookieAmount = 0;
    CookieNumber totalcookies = 0;

};


#endif
