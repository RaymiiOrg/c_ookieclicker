#ifndef C_OOKIECLIKER_COOKIESPERSECONDACHIEVEMENT_H
#define C_OOKIECLIKER_COOKIESPERSECONDACHIEVEMENT_H

#include "Achievement.h"
#include "notifyMessage.h"
#include "CookieNumbers.h"
#include <vector>

class CookiesPerSecondAchievement : public Achievement
{
public:
    CookiesPerSecondAchievement(const CookieNumber& amount, const std::string& name, notifyMessage* msg);
    bool hasAchieved() const override;
    std::string name() override;
    std::string description() override;
    void update(Subject *subject) override;

private:
    notifyMessage* msg;
    CookieNumber _amountRequired;
    std::string _name;
    bool _hasAchieved = false;
    cnp cp;
    void unlockAchievement();
};

#endif //C_OOKIECLIKER_COOKIESPERSECONDACHIEVEMENT_H
