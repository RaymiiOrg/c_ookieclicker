#ifndef C_OOKIECLIKER_INPUTMODEVIEW_H
#define C_OOKIECLIKER_INPUTMODEVIEW_H

#include "ICookieStats.h"
#include "View.h"
#include <vector>

/** The bar that shows which input mode we're in.
 * e.g. store, inventory, upgrades.
 */
class InputModeView : public View
{
    View *currentActiveView = nullptr;
    const std::string _name {"InputMode"};
    const std::vector<View *> &allviews;
    ICookieStats *cookieStats = nullptr;
    void inputBar();
    static void clearLines();
    void renderGetCookie() const;

public:
    void render() override;
    const std::string &name() override { return _name; };
    void setCurrentActiveView(View *currentView) { currentActiveView = currentView; };
    void handleInput(const std::string &input) override;
    explicit InputModeView(const std::vector<View *> &allViews, ICookieStats *cookieStats) :
        allviews(allViews), cookieStats(cookieStats) {};

};

#endif //C_OOKIECLIKER_INPUTMODEVIEW_H
