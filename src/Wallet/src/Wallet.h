//
// Created by remy on 21-04-20.
//

#ifndef C_OOKIECLIKER_WALLET_H
#define C_OOKIECLIKER_WALLET_H

#include "CookieNumber.h"

class Wallet {
public:
    long double getCookieAmount() const;
    long double getCps() const;
    void incrementCookieAmount(long double amount);
    void decrementCookieAmount(long double amount);
    void incrementCps(long double amount);
    unsigned long long  getTotalcookies() const;
private:
    long double cps ;
    long double cookieAmount ;
    unsigned long long totalcookies ;

};


#endif //C_OOKIECLIKER_COOKIENUMBER_H
