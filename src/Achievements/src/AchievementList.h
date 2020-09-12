//
// Created by remy on 21-04-20.
//

#ifndef C_OOKIECLIKER_Achievements_H
#define C_OOKIECLIKER_Achievements_H

#include "Achievement.h"
#include "notifyMessage.h"
#include "CookieAmountAchievement.h"
#include "CookieNumbers.h"
#include "CookiesPerSecondAchievement.h"
#include "Observer.h"
#include "filesystem.h"
#include <fstream>

template <typename T>
class AchievementList : public Observer
{
    std::vector<T *> achievements;
    notifyMessage* msg;

public:
    explicit AchievementList(std::vector<T *> achievements, notifyMessage* msg) :
        achievements(achievements), msg(msg) {};
    void update(Subject *_s) override;
    ~AchievementList() override;

    void loadAchievementsFromCSV(const std::string &filename);
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
}

template <typename T>
void AchievementList<T>::loadAchievementsFromCSV(const std::string &filename)
{
    if (!fs::exists(filename))
        throw std::runtime_error("File " + filename + " does not exist");

    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> params;
        std::stringstream row(line);
        std::string data;
        while (std::getline(row, data, ';'))
        {
            if (!data.empty())
                params.push_back(data);
        }
        if (!params.empty())
            achievements.push_back(new T(params, msg));
    }
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
