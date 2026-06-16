#ifndef C_OOKIECLIKER_Achievements_H
#define C_OOKIECLIKER_Achievements_H

#include "Achievement.h"
#include "notifyMessage.h"
#include "CookieNumbers.h"
#include "CookieAmountAchievement.h"
#include "CookiesPerSecondAchievement.h"
#include "CookiesViaInputAchievement.h"
#include "AchievementRepository.h"
#include "IAchievementRewarder.h"
#include "Observer.h"
#include "Subject.h"

template <typename T>
class AchievementList : public Observer
{
    std::vector<T *> achievements;
    notifyMessage* msg;
    int _previousUnlockedCount = 0;

    int countUnlocked() const
    {
        int count = 0;
        for (const T* a : achievements)
            if (a != nullptr && a->hasAchieved())
                ++count;
        return count;
    }

public:
    explicit AchievementList(std::vector<T *> achievements, notifyMessage* msg) :
        achievements(achievements), msg(msg) {};
    void update(Subject *_s) override;
    ~AchievementList() override;

    void loadFromRepository(const std::vector<AchievementMilestone> &milestones);
    std::vector<T *> getAchievements() const { return achievements; };
};

template <typename T>
void AchievementList<T>::update(Subject *_s)
{
    for (T *a : achievements)
    {
        if (a != nullptr)
            a->update(_s);
    }

    auto *rewarder = dynamic_cast<IAchievementRewarder *>(_s);
    if (rewarder != nullptr)
    {
        int nowUnlocked = countUnlocked();
        int newlyUnlocked = nowUnlocked - _previousUnlockedCount;
        if (newlyUnlocked > 0)
        {
            rewarder->addAchievementBonus(IAchievementRewarder::bonusPerAchievement * CookieNumber(newlyUnlocked));
            _previousUnlockedCount = nowUnlocked;
        }
    }
}

template <typename T>
void AchievementList<T>::loadFromRepository(const std::vector<AchievementMilestone> &milestones)
{
    for (const auto &m : milestones)
        achievements.push_back(new T(m.amount, m.name, msg));
}

template <typename T>
AchievementList<T>::~AchievementList()
{
    for (auto p : achievements)
    {
        delete p;
    }
    achievements.clear();
}

#endif
