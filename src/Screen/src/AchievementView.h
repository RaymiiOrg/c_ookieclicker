//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_ACHIEVEMENTVIEW_H
#define C_OOKIECLIKER_ACHIEVEMENTVIEW_H
#include "View.h"

#include <utility>
#include "AchievementList.h"
#include "Achievement.h"
#include "Wallet.h"
#include "notifyMessage.h"

class AchievementView : public View {
    const std::string _name {"Achievements"};
    AchievementList<Achievement>* achievementlist = nullptr;

public:
    void render() override;
    const std::string &name() override { return _name; };
    void handleInput(const std::string &input) override;
    explicit AchievementView(std::string name) : _name(std::move(name)) {};

    template <typename T>
    void setAchievementlist(T *list) {
        achievementlist = reinterpret_cast<AchievementList<Achievement>*>(list);
    }



};


#endif //C_OOKIECLIKER_ACHIEVEMENTVIEW_H
