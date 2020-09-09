#ifndef C_OOKIECLIKER_SCREEN_H
#define C_OOKIECLIKER_SCREEN_H

#include "View.h"
#include "StatusView.h"
#include "StoreView.h"
#include "InventoryView.h"
#include "OptionsView.h"
#include "AchievementView.h"
#include "MessageView.h"
#include "InputModeView.h"
#include <string>

class Screen {
private:
    const Wallet* wallet = nullptr;
    const notifyMessage* currentMsg = nullptr;
    const Inventory* inventory = nullptr;

    /* lower part of screen, can switch between these views */
    StoreView storeview;
    InventoryView inventoryview = InventoryView(inventory);
    OptionsView optionsview;
    AchievementView achievementview;
    View* activeView = dynamic_cast<View*>(&storeview);
    std::vector<View*> allViews = {
            dynamic_cast<View*>(&storeview),
            dynamic_cast<View*>(&inventoryview),
            dynamic_cast<View*>(&achievementview),
            dynamic_cast<View*>(&optionsview),
            };

    /* top part of screen, status, messages and input. Always visible */
    StatusView statusview = StatusView(wallet);
    MessageView messageview = MessageView(currentMsg);
    InputModeView inputmodeview = InputModeView(allViews);

public:
    void render();
    void handleInput(const std::string& input);
    Screen() =default;
    explicit Screen(const Wallet* wallet, const notifyMessage* currentMsg,
                    const Inventory* inventory) :
                    wallet(wallet), currentMsg(currentMsg),
                    inventory(inventory) {};
    void switchActiveView(const std::string &input);
};


#endif
