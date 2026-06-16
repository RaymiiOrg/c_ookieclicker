#include "CookieAmountAchievement.h"
#include "Subject.h"

bool CookieAmountAchievement::hasAchieved() const
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

CookieAmountAchievement::CookieAmountAchievement(const CookieNumber& amount, const std::string& name, notifyMessage *msg) :
    msg(msg), _amountRequired(amount), _name(name)
{
}

std::string CookieAmountAchievement::name()
{
    return _name;
}

void CookieAmountAchievement::update(Subject *subject)
{
    if (dynamic_cast<IWalletReader *>(subject) != nullptr)
    {
        if (!_hasAchieved)
        {
            if (dynamic_cast<IWalletReader *>(subject)->getCookieAmount() >= _amountRequired)
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
        msg->addMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
    }
}
