//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_MESSAGEVIEW_H
#define C_OOKIECLIKER_MESSAGEVIEW_H
#include "View.h"

#include "notifyMessage.h"
#include <utility>

class MessageView : public View
{
private:
    const notifyMessage *msg;
    void clearMessageView() const;
    void showGameTitle() const;
    void showMessage() const;
    const std::string _name {"Messages"};

public:
    void render() override;
    const std::string &name() override { return _name; };
    void handleInput(const std::string &input) override {};
    explicit MessageView(const notifyMessage *msg) :
        msg(msg) {};
};

#endif //C_OOKIECLIKER_MESSAGEVIEW_H
