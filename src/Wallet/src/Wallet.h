//
// Created by remy on 21-04-20.
//

#ifndef C_OOKIECLIKER_WALLET_H
#define C_OOKIECLIKER_WALLET_H


class Wallet {
public:
    long double getCookieAmount() const;
    long double getCps() const;
    void incrementCookieAmount(long double amount = 1);
    void incrementCps(long double amount);

private:
    long double cps {0};
    long double cookieAmount {0};
    long long totalcookies {static_cast<long long>(cookieAmount)};
public:
    long long int getTotalcookies() const;
};


#endif //C_OOKIECLIKER_WALLET_H
