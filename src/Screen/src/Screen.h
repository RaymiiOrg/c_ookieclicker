#ifndef C_OOKIECLIKER_SCREEN_H
#define C_OOKIECLIKER_SCREEN_H

#include "View.h"
#include "StatusView.h"
#include "StoreView.h"
#include "InventoryView.h"
#include "OptionsView.h"
#include "AchievementView.h"
#include "MessageView.h"
#include <string>

class Screen {
private:
    Wallet& wallet;
    notifyMessage currentMsg;

    /* top part of screen, status, messages and input. Always visible */
    StatusView statusview = StatusView(wallet);
    MessageView messageview = MessageView(currentMsg);

    /* lower part of screen, can switch between these views */
    StoreView storeview;
    InventoryView inventoryview;
    OptionsView optionsview;
    AchievementView achievementview;
    View* activeView = dynamic_cast<View*>(&storeview);

public:
    void render();
    void handleInput(const std::string& input);
    explicit Screen(Wallet &wallet, notifyMessage &currentMsg) : wallet(wallet), currentMsg(currentMsg) {};
    void switchActiveView(const std::string &input);
};


#endif
