//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_ACHIEVEMENTVIEW_H
#define C_OOKIECLIKER_ACHIEVEMENTVIEW_H
#include "View.h"

class AchievementView : public View {
    const std::string _name {"Achievements"};
public:
    void render() override;
    const std::string &name() override { return _name; };
    void handleInput(const std::string &input) override;
};


#endif //C_OOKIECLIKER_ACHIEVEMENTVIEW_H
