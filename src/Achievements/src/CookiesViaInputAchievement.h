#ifndef C_OOKIECLIKER_CookiesViaInputAchievement_H
#define C_OOKIECLIKER_CookiesViaInputAchievement_H

#include "Achievement.h"
#include "notifyMessage.h"
#include "CookieNumbers.h"
#include <vector>

class CookiesViaInputAchievement : public Achievement
{
public:
    CookiesViaInputAchievement(const CookieNumber& amount, const std::string& name, notifyMessage* msg);
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

#endif //C_OOKIECLIKER_CookiesViaInputAchievement_H
