//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_ACHIEVEMENTVIEW_H
#define C_OOKIECLIKER_ACHIEVEMENTVIEW_H
#include "View.h"
#include "AchievementList.h"
#include "Achievement.h"
#include "Wallet.h"
#include "notifyMessage.h"
#include "filesystem.h"

class AchievementView : public View {
    const std::string _name {"Achievements"};

    Wallet* wallet;
    notifyMessage* msg;

    enum achievementViews {
        COOKIE_AMOUNT,
        COOKIES_PER_SECOND,
    };
    achievementViews achievementmode = COOKIE_AMOUNT;

    struct achievementViewMapping {
        achievementViews view;
        std::string inputKey;
        std::string description;
    };

    std::vector<achievementViewMapping> achievementviewmap {
            {COOKIE_AMOUNT, "a", "Cookie Amount"},
            {COOKIES_PER_SECOND, "b", "Cookies per Second"},
    };

    template <typename T>
    void showAchievement(const T& achievementList) {
        for (const auto &a : achievementList->getAchievements()) {
            if (a != nullptr && a->hasAchieved()) {
                std::cout << a->name() << ": " << a->description() << std::endl;
            }
        }
    }

    template <typename T>
    void loadAchievements(T achievementList, const std::string& filename) {
        if (wallet && msg) {
            wallet->addObserver(achievementList.get());
            std::string achievementsFile =
                    fs::current_path().string() + filename;
            if (fs::exists(achievementsFile))
                achievementList->loadAchievementsFromCSV(achievementsFile);
            else {
                msg->setLastError("Could not load achievementsfile from '" + filename + "'.");
                msg->setCurrentMessage(notifyMessage::msgType::ERROR);
            }
        }
    }


    std::shared_ptr<AchievementList<CookieAmountAchievement>> cookieAmountAchievements =
            std::make_shared<AchievementList<CookieAmountAchievement>>(std::vector<std::shared_ptr<CookieAmountAchievement>>());
    std::shared_ptr<AchievementList<CookiesPerSecondAchievement>> cookiespersecondAchievements =
            std::make_shared<AchievementList<CookiesPerSecondAchievement>>(std::vector<std::shared_ptr<CookiesPerSecondAchievement>>());


public:
    void render() override;
    const std::string &name() override { return _name; };
    void handleInput(const std::string &input) override;
    explicit AchievementView(Wallet* wallet, notifyMessage* msg);
};


#endif //C_OOKIECLIKER_ACHIEVEMENTVIEW_H
