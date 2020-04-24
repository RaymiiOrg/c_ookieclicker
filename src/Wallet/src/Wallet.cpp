//
// Created by remy on 21-04-20.
//

#include "Wallet.h"

void Wallet::incrementCps(long double amount) {
    cps += amount;
}

long double Wallet::getCookieAmount() const {
    return cookieAmount;
}

long double Wallet::getCps() const {
    return cps;
}

void Wallet::incrementCookieAmount(long double amount) {
    cookieAmount += amount;
    if (amount > 0)
        totalcookies += static_cast<long long>(amount);
}

long long Wallet::getTotalcookies() const {
    return totalcookies;
}
