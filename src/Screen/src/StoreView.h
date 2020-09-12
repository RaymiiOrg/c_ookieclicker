//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_STOREVIEW_H
#define C_OOKIECLIKER_STOREVIEW_H
#include "Store.h"
#include "View.h"

class StoreView : public View
{
    const std::string _name {"Store"};

public:
    const std::string &name() override { return _name; };
    void render() override;
    void handleInput(const std::string &input) override;
};

#endif //C_OOKIECLIKER_STOREVIEW_H
