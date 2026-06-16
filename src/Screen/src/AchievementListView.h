#ifndef C_OOKIECLIKER_ACHIEVEMENTLISTVIEW_H
#define C_OOKIECLIKER_ACHIEVEMENTLISTVIEW_H
#include "Achievement.h"
#include "AchievementList.h"
#include "AchievementRepository.h"
#include "AchievementView.h"
#include "IWalletReader.h"
#include "Subject.h"
#include "View.h"
#include "Globals.h"
#include "notifyMessage.h"


/** Lists the different types of achievements,
 * eg Cookie Amount, Cookies per second,
 * creates and manages subviews per achievement category
 * (AchievementView).
 */
class AchievementListView : public View
{
    const std::string _name {"Achievements"};
    Subject *walletSubject;
    IWalletReader *walletReader;
    notifyMessage *msg;
    void listAchievementViews() const;
    void renderBonusSummary() const;

    template <typename T>
    void loadFromRepository(T *achievementList, const std::vector<AchievementMilestone> &milestones)
    {
        if (walletSubject && msg)
        {
            walletSubject->addObserver(achievementList);
            achievementList->loadFromRepository(milestones);
        }
    }

    template <typename T, typename V>
    void createAchievementView(T *achievementList, V *achievementView, const std::vector<AchievementMilestone> &milestones)
    {
        if (achievementList && achievementView)
        {
            loadFromRepository(achievementList, milestones);
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
    explicit AchievementListView(Subject *walletSubject, IWalletReader *walletReader, notifyMessage *msg);
};

#endif //C_OOKIECLIKER_ACHIEVEMENTLISTVIEW_H
