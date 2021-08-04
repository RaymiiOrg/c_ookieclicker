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
    setMessageTime();
    currentMessage = _currentMessage;
}

void notifyMessage::setMessageTime(const std::string &timeString)
{
    lastMessageTime = currentTime(timeString);
}

std::ostream &operator<<(std::ostream &os, const notifyMessage &message)
{
    if (!message.lastMessageTime.empty())
        os << message.lastMessageTime << ": ";
    switch (message.getCurrentMessage())
    {
    case notifyMessage::msgType::NOT_ENOUGH_MONEY_FOR_ITEM:
        os << "Not enough money to buy " + message.lastItemFailedToBuy;
        break;
    case notifyMessage::msgType::BOUGHT_ITEM:
        os << "You bought " + cp.print(message.lastItemBoughtAmount) + " " + message.lastItemBoughtName + "(s).";
        break;
    case notifyMessage::msgType::MAGIC:
        os << "The answer to life, the universe and everything!";
        break;
    case notifyMessage::msgType::DEBUG:
        os << "A Debug Thing Happened!";
        break;
    case notifyMessage::msgType::SAVED:
        os << "Game saved.";
        break;
    case notifyMessage::msgType::LOADED:
        os << "Loaded saved game from file";
        break;
    case notifyMessage::msgType::ERROR:
        os << "An error occured: " << message.lastError;
        break;
    case notifyMessage::msgType::ACHIEVEMENT_UNLOCKED:
        os << "Achievement unlocked: " << message.lastAchievement + "!";
        break;
    case notifyMessage::msgType::NO_MSG:
    case notifyMessage::msgType::LAST_MSG:
    default:
        os << "";
        break;
    }
    return os;
}
