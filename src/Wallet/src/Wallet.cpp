//
// Created by remy on 21-04-20.
//

#include "Wallet.h"

void Wallet::incrementCps(const CookieNumber amount) {
    _cps += amount;
}

void Wallet::decrementCps(const CookieNumber amount) {
    _cps -= amount;
}

const CookieNumber Wallet::getCookieAmount() {
    return _cookieAmount;
}

const CookieNumber Wallet::getCps() {
    return _cps;
}

void Wallet::incrementCookieAmount(const CookieNumber amount) {
    _cookieAmount += amount;
    _totalcookies += amount;
}

void Wallet::decrementCookieAmount(const CookieNumber amount) {
    _cookieAmount -= amount;
}

const CookieNumber Wallet::getTotalcookies() {
    return _totalcookies;
}

void Wallet::reset() {
    _cookieAmount = 0;
    _totalcookies = 0;
    _cps = 0;
}

void Wallet::setCps(const CookieNumber &cps) {
    _cps = cps;
}

void Wallet::setCookieAmount(const CookieNumber &cookieAmount) {
    _cookieAmount = cookieAmount;
}

void Wallet::setTotalcookies(const CookieNumber &totalcookies) {
    _totalcookies = totalcookies;
}
