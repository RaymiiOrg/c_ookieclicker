//
// Created by remy on 16-07-20.
//

#ifndef C_OOKIECLIKER_COOKIEAMOUNTACHIEVEMENT_H
#define C_OOKIECLIKER_COOKIEAMOUNTACHIEVEMENT_H
#include "Achievement.h"
#include "CookieNumbers.h"
#include "Wallet.h"

class CookieAmountAchievement : public Achievement {
public:
    CookieAmountAchievement(CookieNumber &amountRequired, const std::string& name, Wallet &wallet);
    bool hasAchieved() override;
    std::string name() override;
    std::string description() override;

private:
    CookieNumber& _amountRequired;
    Wallet& _wallet;
    std::string _name;
    cnp cp;
};


#endif //C_OOKIECLIKER_COOKIEAMOUNTACHIEVEMENT_H
