//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_MESSAGEVIEW_H
#define C_OOKIECLIKER_MESSAGEVIEW_H
#include "View.h"
#include "notifyMessage.h"

class MessageView : public View {
private:
    notifyMessage& msg;

public:
    void render() override;
    void handleInput(const std::string &input) override {};
    explicit MessageView(notifyMessage &msg) : msg(msg) {};
};


#endif //C_OOKIECLIKER_MESSAGEVIEW_H
