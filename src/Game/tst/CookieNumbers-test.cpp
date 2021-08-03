#include "CookieNumbers.h"
#include "gtest/gtest.h"

struct CookieNumbersTestSuite : public ::testing::Test
{
    std::unique_ptr<CookieNumberPrinter> cp;
    CookieNumbersTestSuite()
    {
        cp = std::make_unique<CookieNumberPrinter>();
    }
};

TEST_F(CookieNumbersTestSuite, printWithoutSuffix)
{
    testing::internal::CaptureStdout();
    std::vector<CookieNumber> numbers {CookieNumber(1), CookieNumber(10), CookieNumber(11), CookieNumber(45), CookieNumber(99), CookieNumber(100), CookieNumber(135), CookieNumber(999), CookieNumber(1000), CookieNumber(4231), CookieNumber(20000), CookieNumber(43212)};
    for (const auto &n : numbers)
    {
        std::cout << cp->print(n) + " ";
    }
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "1 10 11 45 99 100 135 999 1000 4231 20000 43212 ");
}

TEST_F(CookieNumbersTestSuite, athousand)
{
    testing::internal::CaptureStdout();
    std::vector<CookieNumber> numbers {
        CookieNumber(100000),
    };
    for (const auto &n : numbers)
    {
        std::cout << cp->print(n) + " ";
    }
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "100 thousand ");
}

TEST_F(CookieNumbersTestSuite, printWithSuffix)
{
    testing::internal::CaptureStdout();
    std::vector<CookieNumber> numbers {
        CookieNumber(123456),
        CookieNumber(424242),
        CookieNumber(9999999),
        CookieNumber(42424242),
        CookieNumber(100000000),
        CookieNumber(9999999999),
        CookieNumber(10000000000),
        CookieNumber(100000000001),
        CookieNumber(1000000000000000), // 1 quadrillion
        CookieNumber(10000000000000000), // 10 quadrillion
        CookieNumber(100000000000000000), // 100 quadrillion
        CookieNumber(1000000000000000000), // 1 quintillion
        CookieNumber("10000000000000000000"), // 10 quintillion
        CookieNumber("100000000000000000000"), // 100 quintillion
        CookieNumber("1000000000000000000000"), // 1 sextillion
        CookieNumber("1144719819892401912749029396684122481958005671979101260467392893236621867918257383955449889430362322321133260887721542254157244194509697745617726122395152454650625637283773749439767525187740228611643080"), //1ss
        CookieNumber("29732982334867582149325438874912272258649497973483149622529685538613555010863828154687010115074346034315149633447312785822266082974277863522538340841432531289626639929448668816617338316564681262640080"), // 29rr
    };
    for (const auto &n : numbers)
    {
        std::cout << cp->print(n) + " ";
    }
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "123 thousand 424 thousand 9 million 42 million 100 million 9 billion 10 billion 100 billion 1 quadrillion 10 quadrillion 100 quadrillion 1 quintillion 10 quintillion 100 quintillion 1 sextillion 1ss 29rr ");
}

TEST_F(CookieNumbersTestSuite, floatWithoutSuffix)
{
    testing::internal::CaptureStdout();
    std::vector<CookieNumber> numbers {CookieNumber(0.1), CookieNumber(0.2), CookieNumber(1.2), CookieNumber(3.0001), CookieNumber(4.0), CookieNumber(10.5), CookieNumber(45.389), CookieNumber(200.12), CookieNumber(1000.88), CookieNumber(4231.2), CookieNumber(20000.899), CookieNumber(43212.91)};
    for (const auto &n : numbers)
    {
        std::cout << cp->print(n) + " ";
    }
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "0.1 0.2 1.1 3 4 10.5 45.3 200.1 1000.8 4231.1 20000.8 43212.9 ");
}

TEST_F(CookieNumbersTestSuite, athousandcommaone)
{
    testing::internal::CaptureStdout();
    std::vector<CookieNumber> numbers {
        CookieNumber(100000),
    };
    for (const auto &n : numbers)
    {
        std::cout << cp->print(n) + " ";
    }
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "100 thousand ");
}

TEST_F(CookieNumbersTestSuite, floatWithSuffix)
{
    testing::internal::CaptureStdout();
    std::vector<CookieNumber> numbers {
        CookieNumber(123456.789),
        CookieNumber(424242.897),
        CookieNumber(9999999.8),
        CookieNumber(42424242.87),
        CookieNumber(100000000.000000001),
        CookieNumber(9999999999.8),
        CookieNumber(10000000000.9),
        CookieNumber(100000000001.2),
        CookieNumber(1000000000000000), // 1 quadrillion
        CookieNumber(10000000000000000), // 10 quadrillion
        CookieNumber(100000000000000000), // 100 quadrillion
        CookieNumber(1000000000000000000), // 1 quintillion
        CookieNumber("10000000000000000000"), // 10 quintillion
        CookieNumber("100000000000000000000"), // 100 quintillion
        CookieNumber("1000000000000000000000"), // 1 sextillion
        CookieNumber("1144719819892401912749029396684122481958005671979101260467392893236621867918257383955449889430362322321133260887721542254157244194509697745617726122395152454650625637283773749439767525187740228611643080"), //1ss
        CookieNumber("29732982334867582149325438874912272258649497973483149622529685538613555010863828154687010115074346034315149633447312785822266082974277863522538340841432531289626639929448668816617338316564681262640080"), // 29rr
    };
    for (const auto &n : numbers)
    {
        std::cout << cp->print(n) + " ";
    }
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "123 thousand 424 thousand 9 million 42 million 100 million 9 billion 10 billion 100 billion 1 quadrillion 10 quadrillion 100 quadrillion 1 quintillion 10 quintillion 100 quintillion 1 sextillion 1ss 29rr ");
}

TEST_F(CookieNumbersTestSuite, printCookieIntWithoutSuffix)
{
    testing::internal::CaptureStdout();
    std::vector<CookieInt> numbers {CookieInt(1), CookieInt(10), CookieInt(11), CookieInt(45), CookieInt(99), CookieInt(100), CookieInt(135), CookieInt(999), CookieInt(1000), CookieInt(4231), CookieInt(20000), CookieInt(43212)};
    for (const auto &n : numbers)
    {
        std::cout << cp->print(n) + " ";
    }
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "1 10 11 45 99 100 135 999 1000 4231 20000 43212 ");
}

TEST_F(CookieNumbersTestSuite, printCookieIntWithSuffix)
{
    testing::internal::CaptureStdout();
    std::vector<CookieInt> numbers {
        CookieInt(123456),
        CookieInt(424242),
        CookieInt(9999999),
        CookieInt(42424242),
        CookieInt(100000000),
        CookieInt(9999999999),
        CookieInt(10000000000),
        CookieInt(100000000001),
        CookieInt(1000000000000000), // 1 quadrillion
        CookieInt(10000000000000000), // 10 quadrillion
        CookieInt(100000000000000000), // 100 quadrillion
        CookieInt(1000000000000000000), // 1 quintillion
        CookieInt("10000000000000000000"), // 10 quintillion
        CookieInt("100000000000000000000"), // 100 quintillion
        CookieInt("1000000000000000000000"), // 1 sextillion
        CookieInt("1144719819892401912749029396684122481958005671979101260467392893236621867918257383955449889430362322321133260887721542254157244194509697745617726122395152454650625637283773749439767525187740228611643080"), //1ss
        CookieInt("29732982334867582149325438874912272258649497973483149622529685538613555010863828154687010115074346034315149633447312785822266082974277863522538340841432531289626639929448668816617338316564681262640080"), // 29rr
    };
    for (const auto &n : numbers)
    {
        std::cout << cp->print(n) + " ";
    }
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "123 thousand 424 thousand 9 million 42 million 100 million 9 billion 10 billion 100 billion 1 quadrillion 10 quadrillion 100 quadrillion 1 quintillion 10 quintillion 100 quintillion 1 sextillion 1ss 29rr ");
}
