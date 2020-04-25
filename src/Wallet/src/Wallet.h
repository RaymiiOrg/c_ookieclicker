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
    void decrementCookieAmount(long double amount);
    void incrementCps(long double amount);
    unsigned long long getTotalcookies() const;
private:
    long double cps {0};
    long double cookieAmount {0};
    unsigned long long totalcookies {0};

};


#endif //C_OOKIECLIKER_WALLET_H
