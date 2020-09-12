//
// Created by remy on 11-09-20.
//

#include "CookiesPerSecondAchievement.h"
#include "Wallet.h"

bool CookiesPerSecondAchievement::hasAchieved() {
    return _hasAchieved;
}

std::string CookiesPerSecondAchievement::name() {
    return _name;
}

std::string CookiesPerSecondAchievement::description() {
    if (_amountRequired == CookieNumber(1))
        return "Baking " + cp.print(_amountRequired) + " cookie per second";
    else
        return "Baking " + cp.print(_amountRequired) + " cookies per second";
}

void CookiesPerSecondAchievement::update(Subject *subject) {
    if(dynamic_cast<Wallet*>(subject) != nullptr) {
        if (dynamic_cast<Wallet*>(subject)->getCps() >= _amountRequired) {
            _hasAchieved = true;
        }
    }
}

CookiesPerSecondAchievement::CookiesPerSecondAchievement(const std::vector<std::string> &params) {
    _amountRequired = static_cast<CookieNumber>(params.front());
    _name = params.back();
}
