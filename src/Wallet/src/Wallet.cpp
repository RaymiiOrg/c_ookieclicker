//
// Created by remy on 21-04-20.
//

#include "Wallet.h"

void Wallet::incrementCps(const CookieNumber& amount) {
    cps += amount;
}

void Wallet::decrementCps(const CookieNumber& amount) {
    cps -= amount;
}

const CookieNumber& Wallet::getCookieAmount() {
    return cookieAmount;
}

const CookieNumber& Wallet::getCps() {
    return cps;
}

void Wallet::incrementCookieAmount(const CookieNumber& amount) {
    cookieAmount += amount;
    totalcookies += amount;
}

void Wallet::decrementCookieAmount(const CookieNumber& amount) {
    cookieAmount -= amount;
}

const CookieNumber& Wallet::getTotalcookies() {
    return totalcookies;
}
