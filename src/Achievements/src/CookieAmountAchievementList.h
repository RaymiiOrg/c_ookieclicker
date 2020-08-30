//
// Created by remy on 21-04-20.
//

#ifndef C_OOKIECLIKER_Achievements_H
#define C_OOKIECLIKER_Achievements_H

#include "CookieNumbers.h"
#include "Achievement.h"
#include "CookieAmountAchievement.h"
#include "Observer.h"

class CookieAmountAchievementList : public Observer {
    std::vector<CookieAmountAchievement> achievements;
public:
    void update(Subject* _s) override;
    CookieAmountAchievementList();
};

void CookieAmountAchievementList::update(Subject* _s) {
    for (CookieAmountAchievement& a : achievements) {
        a.update(_s);
    }
}

CookieAmountAchievementList::CookieAmountAchievementList() {
    achievements.push_back(CookieAmountAchievement(1, "Wake & Bake"));
    achievements.push_back(CookieAmountAchievement(CookieNumber(100), "Make some dough"));
}


#endif

