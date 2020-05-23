//
// Created by remy on 21-04-20.
//

#ifndef C_OOKIECLIKER_WALLET_H
#define C_OOKIECLIKER_WALLET_H

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

typedef boost::multiprecision::cpp_int CookieNumber;
typedef boost::multiprecision::cpp_dec_float<0> CookieFloater;

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
