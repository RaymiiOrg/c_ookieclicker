//
// Created by remy on 08-09-20.
//

#ifndef C_OOKIECLIKER_VIEW_H
#define C_OOKIECLIKER_VIEW_H
#include <iostream>
#include <string>

class View
{
public:
    virtual void render() = 0;
    virtual void handleInput(const std::string &input) = 0;
    virtual const std::string &name() = 0;
};

#endif //C_OOKIECLIKER_VIEW_H
