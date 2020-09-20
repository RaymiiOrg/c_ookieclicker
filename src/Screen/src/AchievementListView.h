//
// Created by remy on 12-09-20.
//

#ifndef C_OOKIECLIKER_ACHIEVEMENTLISTVIEW_H
#define C_OOKIECLIKER_ACHIEVEMENTLISTVIEW_H
#include "Achievement.h"
#include "AchievementList.h"
#include "AchievementView.h"
#include "View.h"
#include "Wallet.h"
#include "filesystem.h"
#include "notifyMessage.h"


/** Lists the different types of achievements,
 * eg Cookie Amount, Cookies per second,
 * creates and manages subviews per achievement category
 * (AchievementView).
 */
class AchievementListView : public View
{
    const std::string _name {"Achievements"};
    Wallet *wallet;
    notifyMessage *msg;
    char getCookieInputKey = 'c';
    void listAchievementViews() const;

    template <typename T>
    void loadAchievementsFromCSV(T *achievementList, const std::string &filename)
    {
        if (wallet && msg)
        {
            wallet->addObserver(achievementList);
            std::string achievementsFile = fs::current_path().string() + filename;
            if (fs::exists(achievementsFile))
                achievementList->loadAchievementsFromCSV(achievementsFile);
            else
            {
                msg->setLastError("Could not load achievementsfile from '" + filename + "'.");
                msg->setCurrentMessage(notifyMessage::msgType::ERROR);
            }
        }
    }

    template <typename T, typename V>
    void createAchievementView(T *achievementList, V *achievementView, const std::string &filename)
    {
        if (achievementList && achievementView)
        {
            loadAchievementsFromCSV(achievementList, filename);
            achievementView->setAchievementlist(achievementList);
        }
    }

    AchievementList<CookieAmountAchievement> cookieAmountAchievementList = AchievementList<CookieAmountAchievement>(std::vector<CookieAmountAchievement *>(), msg);
    AchievementView cookieAmountAchievementView = AchievementView("Cookie Amount");

    AchievementList<CookiesPerSecondAchievement> cookiesPerSecondAchievementList = AchievementList<CookiesPerSecondAchievement>(std::vector<CookiesPerSecondAchievement *>(), msg);
    AchievementView cookiesPerSecondView = AchievementView("Cookies Per Second");

    AchievementList<CookiesViaInputAchievement> cookiesViaInputAchievementList = AchievementList<CookiesViaInputAchievement>(std::vector<CookiesViaInputAchievement *>(), msg);
    AchievementView cookiesViaInputView = AchievementView("Cookies via input");

    View *activeView = dynamic_cast<View *>(&cookieAmountAchievementView);
    std::vector<View *> allviews = {
        dynamic_cast<View *>(&cookieAmountAchievementView),
        dynamic_cast<View *>(&cookiesPerSecondView),
        dynamic_cast<View *>(&cookiesViaInputView),
    };

public:
    void render() override;
    void handleInput(const std::string &input) override;
    const std::string &name() override;
    explicit AchievementListView(Wallet *wallet, notifyMessage *msg);
};

#endif //C_OOKIECLIKER_ACHIEVEMENTLISTVIEW_H
