#ifndef C_OOKIECLIKER_ICOOKIESTATS_H
#define C_OOKIECLIKER_ICOOKIESTATS_H

#include "CookieNumbers.h"

class ICookieStats
{
public:
    virtual ~ICookieStats() = default;
    virtual CookieNumber getCookiesPerTap() const = 0;
};

#endif //C_OOKIECLIKER_ICOOKIESTATS_H
