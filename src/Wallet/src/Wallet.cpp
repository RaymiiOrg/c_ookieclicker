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

CookieNumber Wallet::getTotalcookies() const
{
    return _totalcookies;
}

CookieNumber Wallet::getEffectiveCps() const
{
    return _cps * (CookieNumber(1) + _achievementBonusMultiplier);
}

CookieNumber Wallet::getAchievementBonusMultiplier() const
{
    return _achievementBonusMultiplier;
}

void Wallet::addAchievementBonus(const CookieNumber &step)
{
    CookieNumber newBonus = _achievementBonusMultiplier + step;
    CookieNumber maxBonus = maxAchievementBonus;
    _achievementBonusMultiplier = (newBonus > maxBonus) ? maxBonus : newBonus;
}

void Wallet::reset()
{
    _cookieAmount = 0;
    _totalcookies = 0;
    _cps = 0;
    _achievementBonusMultiplier = 0;
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

void Wallet::setAchievementBonusMultiplier(const CookieNumber &multiplier)
{
    _achievementBonusMultiplier = multiplier;
}

void Wallet::incrementCookieViaInput(const CookieNumber &amount)
{
    _cookiesViaInput += amount;
    incrementCookieAmount(amount);
    notify();
}

CookieNumber Wallet::getCookiesViaInput() const
{
    return _cookiesViaInput;
}
