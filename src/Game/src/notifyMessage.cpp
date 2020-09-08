//
// Created by remy on 08-09-20.
//

#include "notifyMessage.h"
#include "CookieNumbers.h"
#include <chrono>

std::string notifyMessage::currentTime(const std::string &formatString)  {
    auto time_point = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(time_point);
    struct tm *time_info = std::localtime(&now_c);
    std::ostringstream os;
    os << std::put_time(time_info, formatString.c_str());
    return os.str();
}

void notifyMessage::setLastItemFailedToBuy(const std::string &lastItemFailedToBuy) {
    notifyMessage::lastItemFailedToBuy = lastItemFailedToBuy;
}

void notifyMessage::setLastItemBoughtName(const std::string &lastItemBoughtName) {
    notifyMessage::lastItemBoughtName = lastItemBoughtName;
}

void notifyMessage::setLastItemBoughtAmount(const CookieNumber &lastItemBoughtAmount) {
    notifyMessage::lastItemBoughtAmount = lastItemBoughtAmount;
}

void notifyMessage::setLastError(const std::string &lastError) {
    notifyMessage::lastError = lastError;
}

void notifyMessage::setLastAchievement(const std::string &lastAchievement) {
    notifyMessage::lastAchievement = lastAchievement;
}

notifyMessage::msgType notifyMessage::getCurrentMessage() const {
    return currentMessage;
}

void notifyMessage::setCurrentMessage(notifyMessage::msgType currentMessage) {
    setMessageTime();
    notifyMessage::currentMessage = currentMessage;
}


void notifyMessage::setMessageTime(const std::string &timeString) {
    lastMessageTime = timeString;
}

std::ostream &operator<<(std::ostream &os, const notifyMessage &message) {
    os << message.lastMessageTime << ": ";
    switch (message.getCurrentMessage()) {
        case notifyMessage::msgType::NOT_ENOUGH_MONEY_FOR_ITEM:
            os << "Not enough money to buy " + message.lastItemFailedToBuy;
        case notifyMessage::msgType::BOUGHT_ITEM:
            os << "You bought " + cp.print(message.lastItemBoughtAmount) + " " +
                   message.lastItemBoughtName + "(s).";
        case notifyMessage::msgType::MAGIC:
            os << "The answer to life, the universe and everything!";
        case notifyMessage::msgType::DEBUG:
            os << "A Debug Thing Happened!";
        case notifyMessage::msgType::SAVED:
            os << "Game saved.";
        case notifyMessage::msgType::LOADED:
            os << "Loaded saved game from file";
        case notifyMessage::msgType::ERROR:
            os << "An error occured: " << message.lastError;
        case notifyMessage::msgType::ACHIEVEMENT_UNLOCKED:
            os << "Achievement unlocked: " << message.lastAchievement + "!";
        case notifyMessage::msgType::NO_MSG:
        case notifyMessage::msgType::LAST_MSG:
        default:
            os << "";
    }
    return os;
}
