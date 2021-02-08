#ifndef C_OOKIECLIKER_OPTIONSVIEW_H
#define C_OOKIECLIKER_OPTIONSVIEW_H
#include "Inventory.h"
#include "ItemStore.h"
#include "View.h"
#include "Wallet.h"
#include "notifyMessage.h"

class OptionsView : public View
{
    const std::string _name {"Options"};
    notifyMessage *msg;
    Wallet *wallet;
    Inventory *inventory;
    ItemStore *store;
    const std::string &savefilename;
    void save();
    void load();

public:
    void render() override;
    const std::string &name() override { return _name; };
    void handleInput(const std::string &input) override;
    OptionsView(notifyMessage *msg, Wallet *wallet, Inventory *inventory, ItemStore *store,
                const std::string &savefilename) :
        msg(msg), wallet(wallet), inventory(inventory), store(store), savefilename(savefilename) {};
};

#endif //C_OOKIECLIKER_OPTIONSVIEW_H
