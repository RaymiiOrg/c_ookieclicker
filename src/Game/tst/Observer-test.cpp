#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "Observer.h"
#include "Subject.h"
#include "gtest/gtest.h"

class testSubject : public Subject
{
    int _test=0;
public:
    void setTest(int test)
    {
        //std::cout << "testSubject setTest" << std::endl;
        this->_test = test;
        notify();
    }
    [[nodiscard]] int getTest() const {return _test;};


};

class testObserver1: public Observer
{
    testSubject* subject = nullptr;
public:
    ~testObserver1() override { if(subject != nullptr) subject->removeObserver(this); }
    void update() override
    {
           if (subject != nullptr) {
               //std::cout << "testObserver1 subject.getTest(): " << subject->getTest() << std::endl;
               _result = subject->getTest();
           }
    }
    int _result=0;
    void setSubject(testSubject* s) {subject = s; subject->addObserver(this);};
};

class testObserver2: public Observer
{
    testSubject* _s = nullptr;
public:
    ~testObserver2() override { if(_s != nullptr) _s->removeObserver(this); }
    void setSubject(testSubject* s) { _s = s; _s->addObserver(this);};
    void update() override {
        if (_s != nullptr) {
            //std::cout << "testObserver2 subject.getTest(): " << subject->getTest() << std::endl;
            _result = _s->getTest();
        }
    }
    int _result=0;
};

TEST(ObserverTestSuite, notSubscribed)
{
    //arrange
    testSubject testsub;
    testObserver1 testobs1;

    //act
    testsub.setTest(10);
    //assert
    ASSERT_EQ(testobs1._result, 0);
}


TEST(ObserverTestSuite, subscribeOneObserver)
{
    //arrange
    testSubject testsub;
    testObserver1 testobs1;
    testObserver2 testobs2;
    testobs1.setSubject(&testsub);

    //act
    testsub.setTest(10);

    //assert
    ASSERT_EQ(testobs1._result, 10);
    ASSERT_EQ(testobs2._result, 0);
}

TEST(ObserverTestSuite, subscribeMultiple)
{
    //arrange
    testSubject testsub;
    testObserver1 testobs1;
    testObserver2 testobs2;
    testobs1.setSubject(&testsub);
    testobs2.setSubject(&testsub);

    //act
    testsub.setTest(10);

    //assert
    ASSERT_EQ(testobs1._result, 10);
    ASSERT_EQ(testobs2._result, 10);
}



TEST(ObserverTestSuite, differentSubjects)
{
    //arrange
    testSubject testsub1;
    testSubject testsub2;
    testObserver1 testobs1;
    testObserver2 testobs2;
    testobs1.setSubject(&testsub1);
    testobs2.setSubject(&testsub2);

    //act
    testsub1.setTest(10);
    testsub2.setTest(90);

    //assert
    ASSERT_EQ(testobs1._result, 10);
    ASSERT_EQ(testobs2._result, 90);
}

#pragma clang diagnostic pop