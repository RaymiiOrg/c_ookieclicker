//
// Created by remy on 21-04-20.
//

#ifndef C_OOKIECLIKER_WALLET_H
#define C_OOKIECLIKER_WALLET_H

#include "CookieNumber.h"

class Wallet {
    public:
    const CookieNumber& getCookieAmount();
    const CookieNumber& getCps();
    void incrementCookieAmount(const CookieNumber& amount);
    void decrementCookieAmount(const CookieNumber& amount);
    void incrementCps(const CookieNumber& amount);
    void decrementCps(const CookieNumber& amount);
    const CookieNumber& getTotalcookies();
private:
    CookieNumber cps ;
    CookieNumber cookieAmount ;
    CookieNumber totalcookies ;

};


#endif
