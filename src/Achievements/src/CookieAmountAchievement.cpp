//
// Created by remy on 16-07-20.
//

#include "CookieAmountAchievement.h"

bool CookieAmountAchievement::hasAchieved() {
    return _hasAchieved;
}

std::string CookieAmountAchievement::description() {
    if (_amountRequired == CookieNumber(1))
        return "Bake " + cp.print(_amountRequired) + " cookie";
    else
        return "Bake " + cp.print(_amountRequired) + " cookies";
}

CookieAmountAchievement::CookieAmountAchievement(const std::vector<std::string>& params)
{
    _amountRequired = static_cast<CookieNumber>(params.front());
    _name = params.back();
}

std::string CookieAmountAchievement::name() {
    return _name;
}

void CookieAmountAchievement::update(Subject *subject) {
    if(dynamic_cast<Wallet*>(subject) != nullptr) {
        if (dynamic_cast<Wallet*>(subject)->getCookieAmount() >= _amountRequired) {
            _hasAchieved = true;
        }
    }
}
