//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_VIEW_H
#define C_OOKIECLIKER_VIEW_H
#include <string>
#include <iostream>

class View {
public:
    virtual void render() = 0;
    virtual void handleInput(const std::string& input) = 0;
};


#endif //C_OOKIECLIKER_VIEW_H
