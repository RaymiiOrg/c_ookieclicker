#ifndef C_OOKIECLIKER_IACHIEVEMENTREWARDER_H
#define C_OOKIECLIKER_IACHIEVEMENTREWARDER_H

#include "CookieNumbers.h"

class IAchievementRewarder
{
public:
    inline static const CookieNumber bonusPerAchievement {"0.01"};

    virtual ~IAchievementRewarder() = default;
    virtual void addAchievementBonus(const CookieNumber &step) = 0;
};

#endif //C_OOKIECLIKER_IACHIEVEMENTREWARDER_H
