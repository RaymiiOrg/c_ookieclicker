//
// Created by remy on 16-07-20.
//

#include "CookieAmountAchievement.h"
#include <utility>

bool CookieAmountAchievement::hasAchieved() {
    return _hasAchieved;
}

std::string CookieAmountAchievement::description() {
    if (_amountRequired == CookieNumber(1))
        return "Bake " + cp.print(_amountRequired) + " cookie";
    else
        return "Bake " + cp.print(_amountRequired) + " cookies";
}

CookieAmountAchievement::CookieAmountAchievement(const CookieNumber& amountRequired, std::string  name)
        : _amountRequired(amountRequired), _name(std::move(name)) {
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
