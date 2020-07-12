#include "gtest/gtest.h"
#include "CookieNumbers.h"

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
    std::vector<CookieNumber> numbers{CookieNumber(1),
                                      CookieNumber(10),
                                      CookieNumber(11),
                                      CookieNumber(45),
                                      CookieNumber(99),
                                      CookieNumber(100),
                                      CookieNumber(135),
                                      CookieNumber(999),
                                      CookieNumber(1000),
                                      CookieNumber(4231),
                                      CookieNumber(20000),
                                      CookieNumber(43212),
                                      CookieNumber(424242),
                                      CookieNumber(9999999),
                                      CookieNumber(42424242),
                                      CookieNumber(100000000),
                                      CookieNumber(9999999999),
                                      CookieNumber(10000000000),
                                      CookieNumber(100000000001)
    };
    for (const auto& n : numbers) {
        std::cout << cp->print(n) + " ";
    }
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "1 10 11 45 99 100 135 999 1000 4231 20000 43212 424 thousand 9 million 42 million 100 million 9 billion 10 billion 100 billion ");
}


TEST_F(CookieNumbersTestSuite, printWithSufhkjhkjhfix)
{
    //CookieNumber a("29732982334867582149325438874912272258649497973483149622529685538613555010863828154687010115074346034315149633447312785822266082974277863522538340841432531289626639929448668816617338316564681262640080.0"); // 29rr
    //CookieInt b("29732982334867582149325438874912272258649497973483149622529685538613555010863828154687010115074346034315149633447312785822266082974277863522538340841432531289626639929448668816617338316564681262640080"); // 29rr
    CookieNumber a("1.001");
    CookieInt b(1);


    std::cout << "a" << std::endl << cp->print(a) << std::endl;
    std::cout << "b" << std::endl << cp->print(b) << std::endl;
}

TEST_F(CookieNumbersTestSuite, printWithSuffix)
{
    testing::internal::CaptureStdout();
    std::vector<CookieNumber> numbers{CookieNumber(1000000000000000), // 1 quadrillion
                                      CookieNumber(10000000000000000), // 10 quadrillion
                                      CookieNumber(100000000000000000), // 100 quadrillion
                                      CookieNumber(1000000000000000000), // 1 quintillion
                                      CookieNumber("10000000000000000000"), // 10 quintillion
                                      CookieNumber("100000000000000000000"), // 100 quintillion
                                      CookieNumber("1000000000000000000000"), // 1 sextillion
                                      CookieNumber("1144719819892401912749029396684122481958005671979101260467392893236621867918257383955449889430362322321133260887721542254157244194509697745617726122395152454650625637283773749439767525187740228611643080"), //1ss
                                      CookieNumber("29732982334867582149325438874912272258649497973483149622529685538613555010863828154687010115074346034315149633447312785822266082974277863522538340841432531289626639929448668816617338316564681262640080"), // 29rr
    };
    for (const auto& n : numbers) {
        std::cout << cp->print(n) + " ";
    }
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "1 quadrillion 10 quadrillion 100 quadrillion 1 quintillion 10 quintillion 100 quintillion 1 sextillion 1ss 29rr ");
}


TEST_F(CookieNumbersTestSuite, floatWithoutSuffix)
{
    testing::internal::CaptureStdout();
    std::vector<CookieNumber> numbers{CookieNumber(0.1),
                                      CookieNumber(0.2),
                                      CookieNumber(1.2),
                                      CookieNumber(3),
                                      CookieNumber(4.0),
                                      CookieNumber(10.5),
                                      CookieNumber(45.389),
                                      CookieNumber(200.12),
                                      CookieNumber(1000.88),
                                      CookieNumber(4231.2),
                                      CookieNumber(20000.899),
                                      CookieNumber(43212.1),
                                      CookieNumber(424242.897),
                                      CookieNumber(9999999.8),
                                      CookieNumber(42424242.87),
                                      CookieNumber(100000000.1),
                                      CookieNumber(9999999999.8),
                                      CookieNumber(10000000000.9),
                                      CookieNumber(100000000001.2)
    };
    for (const auto& n : numbers) {
        std::cout << cp->print(n) + " ";
    }
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "1 10 11 45 99 100 135 999 1000 4231 20000 43212 424 thousand 9 million 42 million 100 million 9 billion 10 billion 100 billion ");
}

TEST_F(CookieNumbersTestSuite, floatWithSuffix)
{
    testing::internal::CaptureStdout();
    std::vector<CookieNumber> numbers{CookieNumber(1000000000000000), // 1 quadrillion
                                      CookieNumber(10000000000000000), // 10 quadrillion
                                      CookieNumber(100000000000000000), // 100 quadrillion
                                      CookieNumber(1000000000000000000), // 1 quintillion
                                      CookieNumber("10000000000000000000"), // 10 quintillion
                                      CookieNumber("100000000000000000000"), // 100 quintillion
                                      CookieNumber("1000000000000000000000"), // 1 sextillion
                                      CookieNumber("1144719819892401912749029396684122481958005671979101260467392893236621867918257383955449889430362322321133260887721542254157244194509697745617726122395152454650625637283773749439767525187740228611643080"), //1ss
                                      CookieNumber("29732982334867582149325438874912272258649497973483149622529685538613555010863828154687010115074346034315149633447312785822266082974277863522538340841432531289626639929448668816617338316564681262640080"), // 29rr
    };
    for (const auto& n : numbers) {
        std::cout << cp->print(n) + " ";
    }
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "1 quadrillion 10 quadrillion 100 quadrillion 1 quintillion 10 quintillion 100 quintillion 1 sextillion 1ss 29rr ");
}