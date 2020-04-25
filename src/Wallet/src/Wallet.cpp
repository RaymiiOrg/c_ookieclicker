//
// Created by remy on 21-04-20.
//

#include "Wallet.h"

void Wallet::incrementCps(boost::multiprecision::cpp_dec_float_100 amount) {
    cps += amount;
}

boost::multiprecision::cpp_dec_float_100 Wallet::getCookieAmount() const {
    return cookieAmount;
}

boost::multiprecision::cpp_dec_float_100 Wallet::getCps() const {
    return cps;
}

void Wallet::incrementCookieAmount(boost::multiprecision::cpp_dec_float_100 amount) {
    cookieAmount += amount;
    if (amount > 0.0)
        totalcookies += amount;
}

void Wallet::decrementCookieAmount(boost::multiprecision::cpp_dec_float_100 amount) {
    if (cookieAmount >= amount)
        cookieAmount -= amount;
}

boost::multiprecision::cpp_dec_float_100 Wallet::getTotalcookies() const {
    return totalcookies;
}
