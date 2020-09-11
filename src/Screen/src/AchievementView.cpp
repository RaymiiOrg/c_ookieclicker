//
// Created by remy on 08-09-20.
//

#include "AchievementView.h"
#include "terminalCodes.h"

void AchievementView::render() {
    std::cout << "\n===== Achievements ====\n";
    for (const auto& mapping : achievementviewmap) {
        if (achievementmode == mapping.view) {
            std::cout << escapeCode.terminalBold << "[" << mapping.inputKey << "]: " << mapping.description << " Achievement" << escapeCode.terminalReset << std::endl;
        } else {
            std::cout << "[" << mapping.inputKey << "]: Show " << mapping.description << " Achievement" << std::endl;
        }
    }

    switch (achievementmode) {
        case COOKIE_AMOUNT:
            showAchievement(cookieAmountAchievements);
            break;
        case COOKIES_PER_SECOND:
            break;
    }
}

void AchievementView::handleInput(const std::string &input) {
        //TODO
        for (const auto& map : achievementviewmap) {
            if (input == map.inputKey) {
                achievementmode = map.view;
            }
        }

}

AchievementView::AchievementView(Wallet *wallet, notifyMessage *msg) : wallet(wallet), msg(msg) {
    loadAchievements(cookieAmountAchievements, "/gamedata/achievements/CookieAmountAchievements.csv");
    loadAchievements(cookiespersecondAchievements, "/gamedata/achievements/CookiesPerSecondAchievements.csv");
}
