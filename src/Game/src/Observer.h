//
// Created by remy on 26-08-20.
//

#ifndef C_OOKIECLIKER_OBSERVER_H
#define C_OOKIECLIKER_OBSERVER_H

/** Observer, Subscriber, etc **/
class Subject;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(Subject* subject) = 0;
};


#endif //C_OOKIECLIKER_OBSERVER_H
