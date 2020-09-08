//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_NOTIFYMESSAGE_H
#define C_OOKIECLIKER_NOTIFYMESSAGE_H
#include <string>
#include <ostream>
#include "CookieNumbers.h"

class notifyMessage {
public:
    enum class msgType {
        NO_MSG,
        NOT_ENOUGH_MONEY_FOR_ITEM,
        BOUGHT_ITEM,
        MAGIC,
        DEBUG,
        SAVED,
        LOADED,
        ERROR,
        ACHIEVEMENT_UNLOCKED,
        LAST_MSG,
    };
    void setLastItemFailedToBuy(const std::string &lastItemFailedToBuy);
    void setLastItemBoughtName(const std::string &lastItemBoughtName);
    void setLastError(const std::string &lastError);
    void setLastAchievement(const std::string &lastAchievement);
    msgType getCurrentMessage() const;

    friend std::ostream &operator<<(std::ostream &os, const notifyMessage &message);

    void setCurrentMessage(msgType currentMessage);
    void setLastItemBoughtAmount(const CookieNumber &lastItemBoughtAmount);

private:
    msgType currentMessage;
    std::string lastMessageTime;
    CookieNumber lastItemBoughtAmount;
    std::string lastItemFailedToBuy;
    std::string lastItemBoughtName;
    std::string lastError;
    std::string lastAchievement;
    static std::string currentTime(const std::string &formatString);
    void setMessageTime(const std::string& timeString = "%H:%M:%S");

};


#endif //C_OOKIECLIKER_NOTIFYMESSAGE_H
