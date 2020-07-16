//
// Created by remy on 16-07-20.
//

#include "CookieAmountAchievement.h"

bool CookieAmountAchievement::hasAchieved() {
    return _wallet.getTotalcookies() > _amountRequired;
}

std::string CookieAmountAchievement::description() {
    if (_amountRequired == CookieNumber(1))
        return "Bake " + cp.print(_amountRequired) + " cookie";
    else
        return "Bake " + cp.print(_amountRequired) + " cookies";
}

CookieAmountAchievement::CookieAmountAchievement(CookieNumber &amountRequired, const std::string& name, Wallet &wallet)
        : _amountRequired(amountRequired), _wallet(wallet), _name(name) {

}

std::string CookieAmountAchievement::name() {
    return _name;
}

