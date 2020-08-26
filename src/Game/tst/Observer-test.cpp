#include "Observer.h"
#include "Subject.h"
#include "gtest/gtest.h"

struct ObserverTestSuite : public ::testing::Test
{

    ObserverTestSuite()
    {
    }

};

class ClockTimer : public Subject
{
public:
    void SetTime(int _hour, int _minute, int _second)
    {
        std::cout << "clock setTime" << std::endl;
        this->_hour = _hour;
        this->_minute = _minute;
        this->_second = _second;

        notify();
    }

    int Get_hour() const { return _hour; }
    int Get_minute() const { return _minute; }
    int Get_second() const { return _second; }

private:
    int _hour;
    int _minute;
    int _second;
};

class DigitalClock: public Observer
{
public:
    explicit DigitalClock(ClockTimer& s) : subject(s) { subject.addObserver(*this); }
    ~DigitalClock() { subject.removeObserver(*this); }
    void update(Subject* theChangedSubject) override
    {
           std::cout << "Digital time is " << subject.Get_hour() << ":"
                  << subject.Get_minute() << ":"
                  << subject.Get_second() << std::endl;
    }

private:
    ClockTimer& subject;
};

class AnalogClock: public Observer
{
public:
    explicit AnalogClock(ClockTimer& s) : subject(s) { subject.addObserver(*this); }
    ~AnalogClock() { subject.removeObserver(*this); }
    void update(Subject* theChangedSubject) override {
        std::cout << "Analog time is " << subject.Get_hour() << ":"
                  << subject.Get_minute() << ":"
                  << subject.Get_second() << std::endl;
    }

private:
    ClockTimer& subject;
};

TEST_F(ObserverTestSuite, getEmptyObserver)
{
    ClockTimer timer;

    DigitalClock digitalClock(timer);
    AnalogClock analogClock(timer);

    timer.SetTime(14, 41, 36);
}
