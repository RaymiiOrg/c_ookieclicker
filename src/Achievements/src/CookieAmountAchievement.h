#ifndef C_OOKIECLIKER_COOKIEAMOUNTACHIEVEMENT_H
#define C_OOKIECLIKER_COOKIEAMOUNTACHIEVEMENT_H
#include "Achievement.h"
#include "CookieNumbers.h"
#include "IWalletReader.h"
#include "notifyMessage.h"

class CookieAmountAchievement : public Achievement
{
public:
    CookieAmountAchievement(const CookieNumber& amount, const std::string& name, notifyMessage* msg);
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

#endif //C_OOKIECLIKER_COOKIEAMOUNTACHIEVEMENT_H
