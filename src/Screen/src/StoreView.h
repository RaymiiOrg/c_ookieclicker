//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_STOREVIEW_H
#define C_OOKIECLIKER_STOREVIEW_H
#include "View.h"

class StoreView : public View {
public:
    void render() override;
    void handleInput(const std::string &input) override;
};


#endif //C_OOKIECLIKER_STOREVIEW_H
