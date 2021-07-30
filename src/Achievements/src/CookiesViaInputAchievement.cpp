#include "CookiesViaInputAchievement.h"
#include "Wallet.h"
#include <Game/src/notifyMessage.h>

bool CookiesViaInputAchievement::hasAchieved()
{
    return _hasAchieved;
}

std::string CookiesViaInputAchievement::name()
{
    return _name;
}

std::string CookiesViaInputAchievement::description()
{
    if (_amountRequired == CookieNumber(1))
        return "Make " + cp.print(_amountRequired) + " cookie by pressing [c]";
    else
        return "Make " + cp.print(_amountRequired) + " cookies by pressing [c]";
}

void CookiesViaInputAchievement::update(Subject *subject)
{
    if (dynamic_cast<Wallet *>(subject) != nullptr)
    {
        if (!_hasAchieved)
        {
            if (dynamic_cast<Wallet *>(subject)->getCookiesViaInput() >= _amountRequired)
            {
                unlockAchievement();
            }
        }
    }
}

void CookiesViaInputAchievement::unlockAchievement()
{
    _hasAchieved = true;
    if (msg)
    {
        msg->setLastAchievement(_name + ": " + description());
        msg->setCurrentMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
    }
}

CookiesViaInputAchievement::CookiesViaInputAchievement(const std::vector<std::string> &params, notifyMessage *msg) :
    msg(msg)
{
    _amountRequired = static_cast<CookieNumber>(params.front());
    _name = params.back();
}
