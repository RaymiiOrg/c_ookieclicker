//
// Created by remy on 11-09-20.
//

#include <Game/src/notifyMessage.h>
#include "CookiesPerSecondAchievement.h"
#include "Wallet.h"

bool CookiesPerSecondAchievement::hasAchieved()
{
    return _hasAchieved;
}

std::string CookiesPerSecondAchievement::name()
{
    return _name;
}

std::string CookiesPerSecondAchievement::description()
{
    if (_amountRequired == CookieNumber(1))
        return "Bake " + cp.print(_amountRequired) + " cookie per second";
    else
        return "Bake " + cp.print(_amountRequired) + " cookies per second";
}

void CookiesPerSecondAchievement::update(Subject *subject)
{
    if (dynamic_cast<Wallet *>(subject) != nullptr)
    {
        if (!_hasAchieved) {
            if (dynamic_cast<Wallet *>(subject)->getCps() >= _amountRequired) {
                unlockAchievement();
            }
        }
    }
}

void CookiesPerSecondAchievement::unlockAchievement() {
    _hasAchieved = true;
    if (msg) {
        msg->setLastAchievement(_name + ": " + description());
        msg->setCurrentMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
    }
}

CookiesPerSecondAchievement::CookiesPerSecondAchievement(const std::vector<std::string> &params, notifyMessage* msg) :
msg(msg)
{
    _amountRequired = static_cast<CookieNumber>(params.front());
    _name = params.back();
}
