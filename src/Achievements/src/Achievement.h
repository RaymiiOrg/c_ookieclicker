//
// Created by remy on 13-07-20.
//

#ifndef C_OOKIECLIKER_ACHIEVEMENT_H
#define C_OOKIECLIKER_ACHIEVEMENT_H
#include <string>
class Achievement {
public:

    virtual void apply() = 0;
    virtual std::string description() = 0;

};
#endif //C_OOKIECLIKER_ACHIEVEMENT_H
