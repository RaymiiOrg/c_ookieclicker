//
// Created by remy on 13-07-20.
//

#ifndef C_OOKIECLIKER_ACHIEVEMENT_H
#define C_OOKIECLIKER_ACHIEVEMENT_H
#include <string>
#include "Observer.h"

class Achievement : public Observer {
public:
    void update(Subject* subject) override = 0;
    virtual bool hasAchieved() = 0;
    virtual std::string name() = 0;
    virtual std::string description() = 0;

};
#endif //C_OOKIECLIKER_ACHIEVEMENT_H
