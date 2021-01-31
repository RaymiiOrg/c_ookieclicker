#include "AchievementView.h"
#include "terminalCodes.h"

void AchievementView::render()
{
    if (achievementlist != nullptr)
    {
        bool atLeastOne = false;
        for (const auto &a : achievementlist->getAchievements())
        {
            if (a != nullptr && a->hasAchieved())
            {
                atLeastOne = true;
                std::cout << " - " << a->name() << ": " << a->description() << std::endl;
            }
        }
        if (!atLeastOne)
        {
            std::cout << "No " << _name << " achievements unlocked yet." << std::endl;
        }
    }
}

void AchievementView::handleInput(const std::string &input)
{
}
