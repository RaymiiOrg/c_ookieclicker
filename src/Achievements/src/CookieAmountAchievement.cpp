#include "CookieAmountAchievement.h"

bool CookieAmountAchievement::hasAchieved()
{
    return _hasAchieved;
}

std::string CookieAmountAchievement::description()
{
    if (_amountRequired == CookieNumber(1))
        return "Bake " + cp.print(_amountRequired) + " cookie";
    else
        return "Bake " + cp.print(_amountRequired) + " cookies";
}

CookieAmountAchievement::CookieAmountAchievement(const std::vector<std::string> &params, notifyMessage *msg) :
    msg(msg)
{
    _amountRequired = static_cast<CookieNumber>(params.front());
    _name = params.back();
}

std::string CookieAmountAchievement::name()
{
    return _name;
}

void CookieAmountAchievement::update(Subject *subject)
{
    if (dynamic_cast<Wallet *>(subject) != nullptr)
    {
        if (!_hasAchieved)
        {
            if (dynamic_cast<Wallet *>(subject)->getCookieAmount() >= _amountRequired)
            {
                unlockAchievement();
            }
        }
    }
}

void CookieAmountAchievement::unlockAchievement()
{
    _hasAchieved = true;
    if (msg)
    {
        msg->setLastAchievement(_name + ": " + description());
        msg->setCurrentMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
    }
}
