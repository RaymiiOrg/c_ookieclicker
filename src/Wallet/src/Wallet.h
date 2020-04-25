//
// Created by remy on 21-04-20.
//

#ifndef C_OOKIECLIKER_WALLET_H
#define C_OOKIECLIKER_WALLET_H
#include "boost/multiprecision/cpp_dec_float.hpp"

class Wallet {
public:
    boost::multiprecision::cpp_dec_float_100 getCookieAmount() const;
    boost::multiprecision::cpp_dec_float_100 getCps() const;
    void incrementCookieAmount(boost::multiprecision::cpp_dec_float_100 amount);
    void decrementCookieAmount(boost::multiprecision::cpp_dec_float_100 amount);
    void incrementCps(boost::multiprecision::cpp_dec_float_100 amount);
    boost::multiprecision::cpp_dec_float_100 getTotalcookies() const;
private:
    boost::multiprecision::cpp_dec_float_100 cps ;
    boost::multiprecision::cpp_dec_float_100 cookieAmount ;
    boost::multiprecision::cpp_dec_float_100 totalcookies ;

};


#endif //C_OOKIECLIKER_WALLET_H
