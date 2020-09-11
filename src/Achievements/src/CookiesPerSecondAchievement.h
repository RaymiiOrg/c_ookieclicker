//
// Created by remy on 11-09-20.
//

#ifndef C_OOKIECLIKER_COOKIESPERSECONDACHIEVEMENT_H
#define C_OOKIECLIKER_COOKIESPERSECONDACHIEVEMENT_H

#include "Achievement.h"
#include "CookieNumbers.h"
#include <vector>

class CookiesPerSecondAchievement : public Achievement {
public:
    explicit CookiesPerSecondAchievement(const std::vector<std::string>& params);
    bool hasAchieved() override;
    std::string name() override;
    std::string description() override;
    void update(Subject *subject) override;

private:
    CookieNumber _amountRequired;
    std::string _name;
    bool _hasAchieved = false;
    cnp cp;

};


#endif //C_OOKIECLIKER_COOKIESPERSECONDACHIEVEMENT_H
