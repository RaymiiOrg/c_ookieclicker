//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_STATUSVIEW_H
#define C_OOKIECLIKER_STATUSVIEW_H
#include "View.h"
#include "Wallet.h"

/** Current amount of cookies and cookies per second **/
class StatusView : public View
{
private:
    const Wallet *wallet;
    const std::string _name {"Status"};

public:
    const std::string &name() override { return _name; };
    explicit StatusView(const Wallet *wallet) :
        wallet(wallet) {};
    void render() override;
    void handleInput(const std::string &input) override;
};

#endif //C_OOKIECLIKER_STATUSVIEW_H
