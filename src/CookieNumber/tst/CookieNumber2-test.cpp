#include "CookieNumber2.h"
#include <memory>
#include <numeric>
#include "gtest/gtest.h"

TEST(CookieNumber2TestSuite, additionSameUnit)
{
    auto c1 = CookieNumber2(1,1);
    auto c2 = CookieNumber2(1,0);
    auto c3 = c1 + c2;
    auto c5 = CookieNumber2(998, 0);
    auto c6 = CookieNumber2(1, 1);
    auto c7 = c5 + c6;
    auto c8 = c6 + c5;
    ASSERT_EQ(c1 + c2, c3);
    ASSERT_EQ(c3.getCookieUnits(0), 2);
    ASSERT_EQ(c3.getCookieUnits(1), 1);
    ASSERT_EQ(c1.getAmountOfUnits(), 9);
    ASSERT_EQ(c2.getAmountOfUnits(), 9);
    ASSERT_EQ(c3.getAmountOfUnits(), 9);
    ASSERT_EQ(c5 + c6, c7);
    ASSERT_EQ(c6 + c5, c8);
    ASSERT_EQ(c7.getCookieUnits(0), 999);
    ASSERT_EQ(c7.getCookieUnits(1), 1);
    ASSERT_EQ(c8.getCookieUnits(0), 999);
    ASSERT_EQ(c8.getCookieUnits(1), 1);
    ASSERT_EQ(c5.getAmountOfUnits(), 9);
    ASSERT_EQ(c6.getAmountOfUnits(), 9);
    ASSERT_EQ(c7.getAmountOfUnits(), 9);
    ASSERT_EQ(c8.getAmountOfUnits(), 9);
}

TEST(CookieNumber2TestSuite, additionToNextUnit)
{
    auto c1 = CookieNumber2(999);
    auto c2 = CookieNumber2(1);
    auto c3 = c1 + c2;
    auto c4 = c2 + c1;
    auto c5 = CookieNumber2(1,1,1,1,999,1);
    auto c6 = CookieNumber2(0,0,0,0,1,1);
    auto c7 = c5 + c6;
    ASSERT_EQ(c1 + c2, c3);
    ASSERT_EQ(c2 + c1, c4);
    ASSERT_EQ(c3.getCookieUnits(0), 0);
    ASSERT_EQ(c3.getCookieUnits(1), 1);
    ASSERT_EQ(c4.getCookieUnits(0), 0);
    ASSERT_EQ(c4.getCookieUnits(1), 1);
    ASSERT_EQ(c1.getAmountOfUnits(), 9);
    ASSERT_EQ(c2.getAmountOfUnits(), 9);
    ASSERT_EQ(c3.getAmountOfUnits(), 9);
    ASSERT_EQ(c4.getAmountOfUnits(), 9);
    ASSERT_EQ(c5.getAmountOfUnits(), 9);
    ASSERT_EQ(c6.getAmountOfUnits(), 9);
    ASSERT_EQ(c7.getAmountOfUnits(), 9);
    ASSERT_EQ(c7.getCookieUnits(4), 0);
    ASSERT_EQ(c7.getCookieUnits(5), 3);
}

TEST(CookieNumber2TestSuite, additionResize)
{
    auto c1 = CookieNumber2(999,999,999,999,999,999,999,999,999);
    auto c2 = CookieNumber2(1);
    auto c3 = c1 + c2;
    ASSERT_EQ(c1 + c2, c3);
    ASSERT_EQ(c3.getCookieUnits(0), 0);
    ASSERT_EQ(c3.getCookieUnits(1), 0);
    ASSERT_EQ(c3.getCookieUnits(2), 0);
    ASSERT_EQ(c3.getCookieUnits(3), 0);
    ASSERT_EQ(c3.getCookieUnits(4), 0);
    ASSERT_EQ(c3.getCookieUnits(5), 0);
    ASSERT_EQ(c3.getCookieUnits(6), 0);
    ASSERT_EQ(c3.getCookieUnits(7), 0);
    ASSERT_EQ(c3.getCookieUnits(8), 0);
    ASSERT_EQ(c3.getCookieUnits(9), 1);
    ASSERT_EQ(c1.getAmountOfUnits(), 9);
    ASSERT_EQ(c2.getAmountOfUnits(), 9);
    ASSERT_EQ(c3.getAmountOfUnits(), 10);
}

TEST(CookieNumber2TestSuite, additionINTMAX)
{
    auto c1 = CookieNumber2(std::numeric_limits<int>::max());
    auto c2 = CookieNumber2(1);
    auto c3 = c1 + c2;
    auto c4 = c1 + c1;
    //INT_MAX==2147483647
    ASSERT_EQ(c1.getCookieUnits(0), 647);
    ASSERT_EQ(c1.getCookieUnits(1), 483);
    ASSERT_EQ(c1.getCookieUnits(2), 147);
    ASSERT_EQ(c1.getCookieUnits(3), 2);

    ASSERT_EQ(c3.getCookieUnits(0), 648);
    ASSERT_EQ(c3.getCookieUnits(1), 483);
    ASSERT_EQ(c3.getCookieUnits(2), 147);
    ASSERT_EQ(c3.getCookieUnits(3), 2);

    ASSERT_EQ(c4.getCookieUnits(0), 294);
    ASSERT_EQ(c4.getCookieUnits(1), 967);
    ASSERT_EQ(c4.getCookieUnits(2), 294);
    ASSERT_EQ(c4.getCookieUnits(3), 4);
}

TEST(CookieNumber2TestSuite, additionIntRhs) {
    auto c1 = CookieNumber2(998);
    auto c2 = c1 + 2;
    auto c3 = 1 + c1;
    ASSERT_EQ(c2.getCookieUnits(0), 0);
    ASSERT_EQ(c2.getCookieUnits(1), 1);
    ASSERT_EQ(c3.getCookieUnits(0), 999);
    ASSERT_EQ(c3.getCookieUnits(1), 0);
}

TEST(CookieNumber2TestSuite, constructorEnormous) {
    auto c1 = CookieNumber2(std::numeric_limits<int>::max(),
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::max());
    ASSERT_EQ(c1.getCookieUnits(0), 647);
    ASSERT_EQ(c1.getCookieUnits(1), 130);
    ASSERT_EQ(c1.getCookieUnits(2), 278);
    ASSERT_EQ(c1.getCookieUnits(3), 280);
    ASSERT_EQ(c1.getCookieUnits(4), 280);
    ASSERT_EQ(c1.getCookieUnits(5), 280);
    ASSERT_EQ(c1.getCookieUnits(6), 280);
    ASSERT_EQ(c1.getCookieUnits(7), 280);
    ASSERT_EQ(c1.getCookieUnits(8), 280);
    ASSERT_EQ(c1.getCookieUnits(9), 633);
    ASSERT_EQ(c1.getCookieUnits(10), 149);
    ASSERT_EQ(c1.getCookieUnits(11), 2);
    ASSERT_EQ(c1.getAmountOfUnits(), 12);
}

TEST(CookieNumber2TestSuite, constructor)
{
    auto justFits = CookieNumber2(999);
    auto tooLarge = CookieNumber2(1000);
    ASSERT_EQ(justFits.getCookieUnits(0), 999);
    ASSERT_EQ(justFits.getCookieUnits(1), 0);
    ASSERT_EQ(tooLarge.getCookieUnits(0), 0);
    ASSERT_EQ(tooLarge.getCookieUnits(1), 1);

}

TEST(CookieNumber2TestSuite, constructorLarge)
{
    auto c1 = CookieNumber2(1000, 999,999,999,999,999,999, 999, 0);
    ASSERT_EQ(c1.getCookieUnits(0), 0);
    ASSERT_EQ(c1.getCookieUnits(1), 0);
    ASSERT_EQ(c1.getCookieUnits(2), 0);
    ASSERT_EQ(c1.getCookieUnits(3), 0);
    ASSERT_EQ(c1.getCookieUnits(4), 0);
    ASSERT_EQ(c1.getCookieUnits(5), 0);
    ASSERT_EQ(c1.getCookieUnits(6), 0);
    ASSERT_EQ(c1.getCookieUnits(7), 0);
    ASSERT_EQ(c1.getCookieUnits(8), 1);
    ASSERT_EQ(c1.getAmountOfUnits(), 9);
}

TEST(CookieNumber2TestSuite, constructorResize)
{
    auto c1 = CookieNumber2(1000, 999,999,999,999,999,999,999,999);
    ASSERT_EQ(c1.getCookieUnits(0), 0);
    ASSERT_EQ(c1.getCookieUnits(1), 0);
    ASSERT_EQ(c1.getCookieUnits(2), 0);
    ASSERT_EQ(c1.getCookieUnits(3), 0);
    ASSERT_EQ(c1.getCookieUnits(4), 0);
    ASSERT_EQ(c1.getCookieUnits(5), 0);
    ASSERT_EQ(c1.getCookieUnits(6), 0);
    ASSERT_EQ(c1.getCookieUnits(7), 0);
    ASSERT_EQ(c1.getCookieUnits(8), 0);
    ASSERT_EQ(c1.getCookieUnits(9), 1);
    ASSERT_EQ(c1.getAmountOfUnits(), 10);
}

TEST(CookieNumber2TestSuite, multiplicationIntRhs) {
    auto c1 = CookieNumber2(5);
    auto c2 = c1 * 2;
    auto c3 = c1 * 999;
    ASSERT_EQ(c2.getCookieUnits(0), 10);
    ASSERT_EQ(c2.getCookieUnits(1), 0);
    ASSERT_EQ(c3.getCookieUnits(0), 995);
    ASSERT_EQ(c3.getCookieUnits(1), 4);
}

TEST(CookieNumber2TestSuite, multiplication) {
    auto c1 = CookieNumber2(5);
    auto c2 = CookieNumber2(2);
    auto c3 = c1 * c2;
    auto c4 = CookieNumber2(999);
    auto c5 = CookieNumber2(5);
    auto c6 = c4 * c5;
    ASSERT_EQ(c3.getCookieUnits(0), 10);
    ASSERT_EQ(c3.getCookieUnits(1), 0);
    ASSERT_EQ(c6.getCookieUnits(0), 995);
    ASSERT_EQ(c6.getCookieUnits(1), 4);
}

TEST(CookieNumber2TestSuite, largeMultiplicationIntRhs) {
    auto c1 = CookieNumber2(std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max());
    auto c2 = c1 * 2;
    ASSERT_EQ(c2.getCookieUnits(0), 294);
    ASSERT_EQ(c2.getCookieUnits(1), 261);
    ASSERT_EQ(c2.getCookieUnits(2), 556);
    ASSERT_EQ(c2.getCookieUnits(3), 560);
    ASSERT_EQ(c2.getCookieUnits(4), 560);
    ASSERT_EQ(c2.getCookieUnits(5), 560);
    ASSERT_EQ(c2.getCookieUnits(6), 560);
    ASSERT_EQ(c2.getCookieUnits(7), 560);
    ASSERT_EQ(c2.getCookieUnits(8), 560);
    ASSERT_EQ(c2.getCookieUnits(9), 266);
    ASSERT_EQ(c2.getCookieUnits(10), 299);
    ASSERT_EQ(c2.getCookieUnits(11), 4);
}

TEST(CookieNumber2TestSuite, largeMultiplication) {
    auto c1 = CookieNumber2(std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max());
    auto c2 = c1 * c1;
    auto c3 = c2 * c2;
    auto c4 = c3 * c3;
    auto c5 = c4 * c4;

    ASSERT_EQ(c1.getCookieUnits(0),647);
    ASSERT_EQ(c1.getCookieUnits(1),130);
    ASSERT_EQ(c1.getCookieUnits(2),278);
    ASSERT_EQ(c1.getCookieUnits(3),280);
    ASSERT_EQ(c1.getCookieUnits(4),280);
    ASSERT_EQ(c1.getCookieUnits(5),280);
    ASSERT_EQ(c1.getCookieUnits(6),280);
    ASSERT_EQ(c1.getCookieUnits(7),280);
    ASSERT_EQ(c1.getCookieUnits(8),280);
    ASSERT_EQ(c1.getCookieUnits(9),633);
    ASSERT_EQ(c1.getCookieUnits(10),149);
    ASSERT_EQ(c1.getCookieUnits(11),2);

    ASSERT_EQ(c2.getCookieUnits(0),609);
    ASSERT_EQ(c2.getCookieUnits(1),318);
    ASSERT_EQ(c2.getCookieUnits(2),301);
    ASSERT_EQ(c2.getCookieUnits(3),477);
    ASSERT_EQ(c2.getCookieUnits(4),478);
    ASSERT_EQ(c2.getCookieUnits(5),478);
    ASSERT_EQ(c2.getCookieUnits(6),478);
    ASSERT_EQ(c2.getCookieUnits(7),478);
    ASSERT_EQ(c2.getCookieUnits(8),478);
    ASSERT_EQ(c2.getCookieUnits(9),767);
    ASSERT_EQ(c2.getCookieUnits(10),601);
    ASSERT_EQ(c2.getCookieUnits(11),26);

    ASSERT_EQ(c3.getCookieUnits(0),881);
    ASSERT_EQ(c3.getCookieUnits(1),494);
    ASSERT_EQ(c3.getCookieUnits(2),702);
    ASSERT_EQ(c3.getCookieUnits(3),619);
    ASSERT_EQ(c3.getCookieUnits(4),711);
    ASSERT_EQ(c3.getCookieUnits(5),712);
    ASSERT_EQ(c3.getCookieUnits(6),712);
    ASSERT_EQ(c3.getCookieUnits(7),712);
    ASSERT_EQ(c3.getCookieUnits(8),712);
    ASSERT_EQ(c3.getCookieUnits(9),517);
    ASSERT_EQ(c3.getCookieUnits(10),789);
    ASSERT_EQ(c3.getCookieUnits(11),37);
    ASSERT_EQ(c3.getCookieUnits(12),1);

    ASSERT_EQ(c4.getCookieUnits(0),161);
    ASSERT_EQ(c4.getCookieUnits(1),812);
    ASSERT_EQ(c4.getCookieUnits(2),48);
    ASSERT_EQ(c4.getCookieUnits(3),654);
    ASSERT_EQ(c4.getCookieUnits(4),904);
    ASSERT_EQ(c4.getCookieUnits(5),449);
    ASSERT_EQ(c4.getCookieUnits(6),451);
    ASSERT_EQ(c4.getCookieUnits(7),451);
    ASSERT_EQ(c4.getCookieUnits(8),451);
    ASSERT_EQ(c4.getCookieUnits(9),796);
    ASSERT_EQ(c4.getCookieUnits(10),788);
    ASSERT_EQ(c4.getCookieUnits(11),991);
    ASSERT_EQ(c4.getCookieUnits(12),2);

    ASSERT_EQ(c5.getCookieUnits(0),921);
    ASSERT_EQ(c5.getCookieUnits(1),369);
    ASSERT_EQ(c5.getCookieUnits(2),963);
    ASSERT_EQ(c5.getCookieUnits(3),718);
    ASSERT_EQ(c5.getCookieUnits(4),643);
    ASSERT_EQ(c5.getCookieUnits(5),418);
    ASSERT_EQ(c5.getCookieUnits(6),603);
    ASSERT_EQ(c5.getCookieUnits(7),604);
    ASSERT_EQ(c5.getCookieUnits(8),604);
    ASSERT_EQ(c5.getCookieUnits(9),819);
    ASSERT_EQ(c5.getCookieUnits(10),577);
    ASSERT_EQ(c5.getCookieUnits(11),702);
    ASSERT_EQ(c5.getCookieUnits(12),986);

}

TEST(CookieNumber2TestSuite, substract) {

    auto c1 = CookieNumber2(5000);
    std::cout << c1;
    auto c2 = CookieNumber2(2500);
    auto c3 = c1 - c2;

    //std::cout << "c3: " << c3 << std::endl;
    ASSERT_EQ(c3.getCookieUnits(0), 500);
    ASSERT_EQ(c3.getCookieUnits(1), 500);

}

TEST(CookieNumber2TestSuite, output) {
    testing::internal::CaptureStdout();

    std::cout << CookieNumber2(1234);
    std::string o1 = testing::internal::GetCapturedStdout();

    ASSERT_EQ(o1, "1234");
}

TEST(CookieNumber2TestSuite, output_zeros) {
    testing::internal::CaptureStdout();

    std::cout << CookieNumber2(5000);
    std::string o1 = testing::internal::GetCapturedStdout();

    ASSERT_EQ(o1, "5000");
}

TEST(CookieNumber2TestSuite, operators) {

    auto c1 = CookieNumber2(5000);
    auto c2 = CookieNumber2(1234);
    bool lt1 = c1 < c2;
    bool gt1 = c1 > c2;
    bool ne1 = c1 != c2;
    bool eq1 = c1 == c2;

    ASSERT_EQ(lt1, false);
    ASSERT_EQ(gt1, true);
    ASSERT_EQ(ne1, true);
    ASSERT_EQ(eq1, false);
}