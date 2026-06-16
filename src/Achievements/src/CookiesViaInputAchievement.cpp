#include "CookiesViaInputAchievement.h"
#include "IWalletReader.h"
#include "Subject.h"
#include <Game/src/notifyMessage.h>

bool CookiesViaInputAchievement::hasAchieved() const
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
    if (dynamic_cast<IWalletReader *>(subject) != nullptr)
    {
        if (!_hasAchieved)
        {
            if (dynamic_cast<IWalletReader *>(subject)->getCookiesViaInput() >= _amountRequired)
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
        msg->addMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
    }
}

CookiesViaInputAchievement::CookiesViaInputAchievement(const CookieNumber& amount, const std::string& name, notifyMessage *msg) :
    msg(msg), _amountRequired(amount), _name(name)
{
}
