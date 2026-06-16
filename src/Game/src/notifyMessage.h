#ifndef C_OOKIECLIKER_NOTIFYMESSAGE_H
#define C_OOKIECLIKER_NOTIFYMESSAGE_H
#include "CookieNumbers.h"
#include <atomic>
#include <mutex>
#include <ostream>
#include <string>
#include <vector>

class notifyMessage
{
public:
    enum class msgType
    {
        NO_MSG,
        NOT_ENOUGH_MONEY_FOR_ITEM,
        BOUGHT_ITEM,
        MAGIC,
        DEBUG,
        SAVED,
        LOADED,
        ERROR,
        ACHIEVEMENT_UNLOCKED,
        COOKIES_PER_TAP,
        BOUGHT_TAP_UPGRADE,
        BOUGHT_CPS_UPGRADE,
        LAST_MSG,
    };
    void setLastItemFailedToBuy(const std::string &lastItemFailedToBuy);
    void setLastItemBoughtName(const std::string &lastItemBoughtName);
    void setLastError(const std::string &lastError);
    void setLastAchievement(const std::string &lastAchievement);
    [[nodiscard]] msgType getCurrentMessage() const;

    friend std::ostream &operator<<(std::ostream &os, const notifyMessage &message);

    /** Replaces any currently shown messages with a single message of this
     * type (rendered from the current data). Use for a new, standalone notice. */
    void setCurrentMessage(msgType currentMessage);

    /** Adds a message of this type alongside the ones already shown, rendering
     * it immediately so it captures the current data. Use when several notices
     * belong together, e.g. an achievement unlocked by the same tap that just
     * granted a cookie. */
    void addMessage(msgType type);

    void setLastItemBoughtAmount(const CookieNumber &lastItemBoughtAmount);

private:
    msgType currentMessage = msgType::NO_MSG;
    std::string lastMessageTime;
    CookieNumber lastItemBoughtAmount;
    std::string lastItemFailedToBuy;
    std::string lastItemBoughtName;
    std::string lastError;
    std::string lastAchievement;
    std::vector<std::string> _messages;
    mutable std::mutex _mutex;
    static std::string currentTime(const std::string &formatString);
    void setMessageTime(const std::string &timeString = "%H:%M:%S");
    /** Renders the body (without timestamp) for a message type from the
     * current data. Empty for types that have no text. */
    std::string renderBody(msgType type) const;
    /** Appends a rendered message; caller must hold _mutex. */
    void addMessageLocked(msgType type);
};

#endif //C_OOKIECLIKER_NOTIFYMESSAGE_H
