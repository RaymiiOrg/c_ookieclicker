//
// Created by remy on 21-04-20.
//

#ifndef C_OOKIECLIKER_WALLET_H
#define C_OOKIECLIKER_WALLET_H

#include "CookieNumber.h"

class Wallet {
    public:
    CookieNumber getCookieAmount() const;
    CookieNumber getCps() const;
    void incrementCookieAmount(CookieNumber amount);
    void decrementCookieAmount(CookieNumber amount);
    void incrementCps(CookieNumber amount);
    CookieNumber  getTotalcookies() const;
private:
    CookieNumber cps ;
    CookieNumber cookieAmount ;
    CookieNumber totalcookies ;

};


#endif
