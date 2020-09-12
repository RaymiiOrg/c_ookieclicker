#ifndef C_OOKIECLIKER_MAINVIEW_H
#define C_OOKIECLIKER_MAINVIEW_H

#include "AchievementListView.h"
#include "InputModeView.h"
#include "InventoryView.h"
#include "MessageView.h"
#include "OptionsView.h"
#include "StatusView.h"
#include "StoreView.h"
#include "View.h"
#include <string>

/** The main game screen, which houses a certain
 * amount of set views (non-changable) and a set
 * of switchable views (via different input keys).
 */
class MainView : public View
{
private:
    const std::string _name { "Main Screen"};
    std::string saveFile = ".cookieclicker.save";
    Wallet *wallet = nullptr;
    notifyMessage *msg = nullptr;
    Inventory *inventory = nullptr;
    Store *store = nullptr;
    void switchActiveView(const std::string &input);

    /* lower part of screen, can switch between these views */
    StoreView storeview = StoreView(msg, wallet, inventory, store);
    InventoryView inventoryview = InventoryView(inventory);
    OptionsView optionsview = OptionsView(msg, wallet, inventory, store, saveFile);
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
    void render() override;
    const std::string &name() override { return _name; };
    void handleInput(const std::string &input) override;
    explicit MainView(notifyMessage *msg, Wallet *wallet, Inventory *inventory, Store *store) :
        wallet(wallet), msg(msg),
        inventory(inventory), store(store) {
        switchActiveView("1");
    };

};

#endif
