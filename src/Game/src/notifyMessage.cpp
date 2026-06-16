#include "notifyMessage.h"
#include "CookieNumbers.h"
#include <chrono>
#include <iomanip>

std::string notifyMessage::currentTime(const std::string &formatString)
{
    auto time_point = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(time_point);
    struct tm *time_info = std::localtime(&now_c);
    std::ostringstream os;
    os << std::put_time(time_info, formatString.c_str());
    return os.str();
}

void notifyMessage::setLastItemFailedToBuy(const std::string &_lastItemFailedToBuy)
{
    lastItemFailedToBuy = _lastItemFailedToBuy;
}

void notifyMessage::setLastItemBoughtName(const std::string &_lastItemBoughtName)
{
    lastItemBoughtName = _lastItemBoughtName;
}

void notifyMessage::setLastItemBoughtAmount(const CookieNumber &_lastItemBoughtAmount)
{
    lastItemBoughtAmount = _lastItemBoughtAmount;
}

void notifyMessage::setLastError(const std::string &_lastError)
{
    lastError = _lastError;
}

void notifyMessage::setLastAchievement(const std::string &_lastAchievement)
{
    lastAchievement = _lastAchievement;
}

notifyMessage::msgType notifyMessage::getCurrentMessage() const
{
    return currentMessage;
}

void notifyMessage::setCurrentMessage(notifyMessage::msgType _currentMessage)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _messages.clear();
    addMessageLocked(_currentMessage);
}

void notifyMessage::addMessage(notifyMessage::msgType type)
{
    std::lock_guard<std::mutex> lock(_mutex);
    addMessageLocked(type);
}

void notifyMessage::addMessageLocked(notifyMessage::msgType type)
{
    setMessageTime();
    currentMessage = type;
    std::string body = renderBody(type);
    if (!body.empty())
        _messages.push_back(body);
}

void notifyMessage::setMessageTime(const std::string &timeString)
{
    lastMessageTime = currentTime(timeString);
}

std::string notifyMessage::renderBody(notifyMessage::msgType type) const
{
    switch (type)
    {
    case notifyMessage::msgType::NOT_ENOUGH_MONEY_FOR_ITEM:
        return "Not enough money to buy " + lastItemFailedToBuy;
    case notifyMessage::msgType::BOUGHT_ITEM: {
        std::string s = (lastItemBoughtAmount == CookieNumber(1)) ? "" : "s";
        return "You bought " + cp.print(lastItemBoughtAmount) + " " + lastItemBoughtName + s + ".";
    }
    case notifyMessage::msgType::BOUGHT_TAP_UPGRADE: {
        std::string noun = (lastItemBoughtAmount == CookieNumber(1)) ? "cookie" : "cookies";
        return "Upgraded to " + lastItemBoughtName + "! +"
               + cp.print(lastItemBoughtAmount) + " " + noun + " per tap.";
    }
    case notifyMessage::msgType::MAGIC:
        return "The answer to life, the universe and everything!";
    case notifyMessage::msgType::DEBUG:
        return "A Debug Thing Happened!";
    case notifyMessage::msgType::SAVED:
        return "Game saved.";
    case notifyMessage::msgType::LOADED:
        return "Loaded saved game from file";
    case notifyMessage::msgType::ERROR:
        return "An error occured: " + lastError;
    case notifyMessage::msgType::ACHIEVEMENT_UNLOCKED:
        return "Achievement unlocked: " + lastAchievement + "!";
    case notifyMessage::msgType::COOKIES_PER_TAP: {
        std::string noun = (lastItemBoughtAmount == CookieNumber(1)) ? "cookie" : "cookies";
        return "Got " + cp.print(lastItemBoughtAmount) + " " + noun + "!";
    }
    case notifyMessage::msgType::BOUGHT_CPS_UPGRADE:
        return lastItemBoughtName + ": +" + cp.print(lastItemBoughtAmount) + "% cps!";
    case notifyMessage::msgType::NO_MSG:
    case notifyMessage::msgType::LAST_MSG:
    default:
        return "";
    }
}

std::ostream &operator<<(std::ostream &os, const notifyMessage &message)
{
    std::lock_guard<std::mutex> lock(message._mutex);
    if (message._messages.empty())
        return os;
    if (!message.lastMessageTime.empty())
        os << message.lastMessageTime << ": ";
    bool first = true;
    for (const auto &body : message._messages)
    {
        if (!first)
            os << " | ";
        os << body;
        first = false;
    }
    return os;
}
