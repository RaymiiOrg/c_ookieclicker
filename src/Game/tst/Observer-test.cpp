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
    public:
    void update(Subject* _s) override
    {
        if (dynamic_cast<testSubject*>(_s) != nullptr) {
            _result = dynamic_cast<testSubject*>(_s)->getTest();
        }
    }
    int _result=0;
};

class testObserver2: public Observer
{
public:
    void update(Subject* _s) override {
        if (dynamic_cast<testSubject*>(_s) != nullptr) {
            _result = dynamic_cast<testSubject*>(_s)->getTest();
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
    testsub.addObserver(&testobs1);

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
    testsub.addObserver(&testobs1);
    testsub.addObserver(&testobs2);

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
    testsub1.addObserver(&testobs1);
    testsub2.addObserver(&testobs2);

    //act
    testsub1.setTest(10);
    testsub2.setTest(90);

    //assert
    ASSERT_EQ(testobs1._result, 10);
    ASSERT_EQ(testobs2._result, 90);
}

#pragma clang diagnostic pop