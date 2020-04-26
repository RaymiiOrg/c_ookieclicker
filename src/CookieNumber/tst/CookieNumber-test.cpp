#include "CookieNumber.h"
#include <memory>
#include "gtest/gtest.h"

struct CookieNumberTestSuite : public ::testing::Test
{
    CookieNumberTestSuite()
    {
    }

};

TEST_F(CookieNumberTestSuite, simple)
{
    auto c1 = CookieNumber(1, 0);
    auto c2 = CookieNumber(1, 1);
    auto c3 = c1 + c2;
    ASSERT_EQ(c1 + c2, c3);
}


TEST_F(CookieNumberTestSuite, simple2)
{
    auto c1 = CookieNumber(998, 0);
    auto c2 = CookieNumber(1, 1);

    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;
    std::cout << "c1 + c2: " << c1 + c2 << std::endl;
    ASSERT_EQ(true, true);
}