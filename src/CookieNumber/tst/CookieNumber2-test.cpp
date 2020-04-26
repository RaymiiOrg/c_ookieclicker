#include "CookieNumber2.h"
#include <memory>
#include "gtest/gtest.h"

struct CookieNumber2TestSuite : public ::testing::Test
{
    CookieNumber2TestSuite()
    {
    }

};

TEST_F(CookieNumber2TestSuite, simple)
{
    auto c1 = CookieNumber2(1,1);
    auto c2 = CookieNumber2(1,0);
    auto c3 = c1 + c2;
    ASSERT_EQ(c1 + c2, c3);
    ASSERT_EQ(c3.getCookieUnits(0), 2);
    ASSERT_EQ(c3.getCookieUnits(1), 1);
}


TEST_F(CookieNumber2TestSuite, simple2)
{
    auto c1 = CookieNumber2(998, 0);
    auto c2 = CookieNumber2(1, 1);
    auto c3 = c1 + c2;
    auto c4 = c2 + c1;
    ASSERT_EQ(c1 + c2, c3);
    ASSERT_EQ(c2 + c1, c4);
    ASSERT_EQ(c3.getCookieUnits(0), 999);
    ASSERT_EQ(c3.getCookieUnits(1), 1);
    ASSERT_EQ(c4.getCookieUnits(0), 999);
    ASSERT_EQ(c4.getCookieUnits(1), 1);
}

TEST_F(CookieNumber2TestSuite, simple3)
{
    auto c1 = CookieNumber2(999, 0);
    auto c2 = CookieNumber2(1, 1);
    auto c3 = c1 + c2;
    auto c4 = c2 + c1;
    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;
    std::cout << "c1 + c2: " << c3 << std::endl;
    std::cout << "c2 + c1: " << c4 << std::endl;
    ASSERT_EQ(c1 + c2, c3);
    ASSERT_EQ(c2 + c1, c4);
    ASSERT_EQ(c3.getCookieUnits(0), 1);
    ASSERT_EQ(c3.getCookieUnits(1), 2);
    ASSERT_EQ(c4.getCookieUnits(0), 1);
    ASSERT_EQ(c4.getCookieUnits(1), 2);
}