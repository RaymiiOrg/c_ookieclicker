//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_STATUSVIEW_H
#define C_OOKIECLIKER_STATUSVIEW_H
#include "View.h"
#include "Wallet.h"

class StatusView : public View {
private:
    Wallet& wallet;
    
public:
    explicit StatusView(Wallet &wallet);
    void render() override;
    void handleInput(const std::string &input) override;
};


#endif //C_OOKIECLIKER_STATUSVIEW_H
