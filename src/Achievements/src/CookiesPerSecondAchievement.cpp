#include "CookiesPerSecondAchievement.h"
#include "IWalletReader.h"
#include "Subject.h"
#include <Game/src/notifyMessage.h>

bool CookiesPerSecondAchievement::hasAchieved() const
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
    if (dynamic_cast<IWalletReader *>(subject) != nullptr)
    {
        if (!_hasAchieved)
        {
            if (dynamic_cast<IWalletReader *>(subject)->getCps() >= _amountRequired)
            {
                unlockAchievement();
            }
        }
    }
}

void CookiesPerSecondAchievement::unlockAchievement()
{
    _hasAchieved = true;
    if (msg)
    {
        msg->setLastAchievement(_name + ": " + description());
        msg->addMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
    }
}

CookiesPerSecondAchievement::CookiesPerSecondAchievement(const CookieNumber& amount, const std::string& name, notifyMessage *msg) :
    msg(msg), _amountRequired(amount), _name(name)
{
}
