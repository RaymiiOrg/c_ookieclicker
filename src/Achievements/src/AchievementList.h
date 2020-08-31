//
// Created by remy on 21-04-20.
//

#ifndef C_OOKIECLIKER_Achievements_H
#define C_OOKIECLIKER_Achievements_H

#include "CookieNumbers.h"
#include "Achievement.h"
#include "CookieAmountAchievement.h"
#include "Observer.h"

template <typename T>
class AchievementList : public Observer {
    std::vector<T> achievements;
public:
    explicit AchievementList(std::vector<T> achievements) : achievements(achievements) {};
    void update(Subject* _s) override {
        for (Achievement *a : achievements) {
            if (a != nullptr)
                a->update(_s);
        }
    }
};


#endif

