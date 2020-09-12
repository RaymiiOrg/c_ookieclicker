//
// Created by remy on 21-04-20.
//

#include "Wallet.h"

void Wallet::incrementCps(const CookieNumber &amount)
{
    _cps += amount;
    notify();
}

void Wallet::decrementCps(const CookieNumber &amount)
{
    _cps -= amount;
    notify();
}

CookieNumber Wallet::getCookieAmount() const
{
    return _cookieAmount;
}

CookieNumber Wallet::getCps() const
{
    return _cps;
}

void Wallet::incrementCookieAmount(const CookieNumber &amount)
{
    _cookieAmount += amount;
    _totalcookies += amount;
    notify();
}

void Wallet::decrementCookieAmount(const CookieNumber &amount)
{
    _cookieAmount -= amount;
    notify();
}

CookieNumber Wallet::getTotalcookies()
{
    return _totalcookies;
}

void Wallet::reset()
{
    _cookieAmount = 0;
    _totalcookies = 0;
    _cps = 0;
    notify();
}

void Wallet::setCps(const CookieNumber &cps)
{
    _cps = cps;
}

void Wallet::setCookieAmount(const CookieNumber &cookieAmount)
{
    _cookieAmount = cookieAmount;
    notify();
}

void Wallet::setTotalcookies(const CookieNumber &totalcookies)
{
    _totalcookies = totalcookies;
}
