#ifndef C_OOKIECLIKER_SCREEN_H
#define C_OOKIECLIKER_SCREEN_H

#include "AchievementListView.h"
#include "InputModeView.h"
#include "InventoryView.h"
#include "MessageView.h"
#include "OptionsView.h"
#include "StatusView.h"
#include "StoreView.h"
#include "View.h"
#include <string>

class Screen
{
private:
    std::string saveFile = ".cookieclicker.save";
    Wallet *wallet = nullptr;
    notifyMessage *msg = nullptr;
    Inventory *inventory = nullptr;
    Store *store = nullptr;

    /* lower part of screen, can switch between these views */
    StoreView storeview;
    InventoryView inventoryview = InventoryView(inventory);
    OptionsView optionsview = OptionsView(msg, saveFile, wallet, inventory, store);
    AchievementListView achievementlistview = AchievementListView(wallet, msg);
    View *activeView = dynamic_cast<View *>(&storeview);
    std::vector<View *> allViews = {
        dynamic_cast<View *>(&storeview),
        dynamic_cast<View *>(&inventoryview),
        dynamic_cast<View *>(&achievementlistview),
        dynamic_cast<View *>(&optionsview),
    };

    /* top part of screen, status, messages and input. Always visible */
    StatusView statusview = StatusView(wallet);
    MessageView messageview = MessageView(msg);
    InputModeView inputmodeview = InputModeView(allViews);

public:
    void render();
    void handleInput(const std::string &input);
    Screen() = default;
    explicit Screen(Wallet *wallet, notifyMessage *currentMsg, Inventory *inventory, Store *store) :
        wallet(wallet), msg(currentMsg),
        inventory(inventory), store(store) {};
    void switchActiveView(const std::string &input);
};

#endif
