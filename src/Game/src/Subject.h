//
// Created by remy on 26-08-20.
//

#ifndef C_OOKIECLIKER_SUBJECT_H
#define C_OOKIECLIKER_SUBJECT_H

#include <vector>
#include <algorithm>
#include "Observer.h"

/** Subject, Publisher **/
class Subject {
    std::vector<Observer*> observers;
public:
    virtual ~Subject() =default;
    void addObserver(Observer* o) { if (o) observers.push_back(o); };
    void removeObserver(Observer* o) { if (o) observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end()); };
    void notify() {
        for (auto o : observers)
            if (o != nullptr)
                o->update(this);
    }
};


#endif //C_OOKIECLIKER_SUBJECT_H
