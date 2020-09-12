//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_OPTIONSVIEW_H
#define C_OOKIECLIKER_OPTIONSVIEW_H
#include "View.h"
#include "notifyMessage.h"

class OptionsView : public View
{
    const std::string _name {"Options"};
    const std::string &savefilename;
    notifyMessage *msg;
    Wallet *wallet;
    Inventory *inventory;
    Store *store;
    void save();
    void load();

public:
    void render() override;
    const std::string &name() override { return _name; };
    void handleInput(const std::string &input) override;
    OptionsView(notifyMessage *msg, const std::string &savefilename, Wallet *wallet, Inventory *inventory, Store *store) :
        msg(msg), savefilename(savefilename),
        wallet(wallet), inventory(inventory), store(store) {};
};

#endif //C_OOKIECLIKER_OPTIONSVIEW_H
