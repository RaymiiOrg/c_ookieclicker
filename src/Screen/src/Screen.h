#ifndef C_OOKIECLIKER_SCREEN_H
#define C_OOKIECLIKER_SCREEN_H

#include "View.h"
#include "StatusView.h"
#include "StoreView.h"
#include "InventoryView.h"
#include "OptionsView.h"
#include "AchievementView.h"
#include <string>

class Screen {
private:
    Wallet& wallet;
    StatusView statusview = StatusView(wallet);
    StoreView storeview;
    InventoryView inventoryview;
    OptionsView optionsview;
    AchievementView achievementview;
    View* activeView = dynamic_cast<View*>(&storeview);

public:
    void render();
    void handleInput(const std::string& input);
    explicit Screen(Wallet& wallet) : wallet(wallet) {};
    void switchActiveView(const std::string &input);
};


#endif
