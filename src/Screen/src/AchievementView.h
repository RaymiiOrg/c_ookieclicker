#ifndef C_OOKIECLIKER_ACHIEVEMENTVIEW_H
#define C_OOKIECLIKER_ACHIEVEMENTVIEW_H
#include "View.h"

#include "Achievement.h"
#include "AchievementList.h"
#include "notifyMessage.h"
#include <utility>

/** Shows the actual achievements **/
class AchievementView : public View
{
    const std::string _name {"Achievements"};
    AchievementList<Achievement> *achievementlist = nullptr;

public:
    void render() override;
    const std::string &name() override { return _name; };
    void handleInput(const std::string &input) override;
    explicit AchievementView(const std::string &name) :
        _name(name) {};

    /** Due to threads, not everything is available at construction,
     * thus we can set it later.
     * @tparam T
     * @param list AchievementList
     */
    template <typename T>
    void setAchievementlist(T *list)
    {
        achievementlist = reinterpret_cast<AchievementList<Achievement> *>(list);
    }
};

#endif //C_OOKIECLIKER_ACHIEVEMENTVIEW_H
