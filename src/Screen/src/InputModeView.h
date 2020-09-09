//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_INPUTMODEVIEW_H
#define C_OOKIECLIKER_INPUTMODEVIEW_H

#include <vector>
#include "View.h"

class InputModeView : public View {
    View* currentActiveView = nullptr;
    const std::string _name {"InputMode"};
    const std::vector<View*>& allviews;

public:
    void render() override;
    const std::string &name() override { return _name; };
    void setCurrentActiveView(View* currentView) { currentActiveView = currentView;};
    void handleInput(const std::string &input) override;
    explicit InputModeView(const std::vector<View*>& allViews) : allviews(allViews) {};

    void inputBar();
};


#endif //C_OOKIECLIKER_INPUTMODEVIEW_H
