#include "gtest/gtest.h"
#define private public
#include "notifyMessage.h"

TEST(notifyMessageTapUpgradeTestSuite, tapUpgradeSingularCookie)
{
    testing::internal::CaptureStdout();
    notifyMessage msg;
    msg.setLastItemBoughtName("Cookie Upgrade");
    msg.setLastItemBoughtAmount(CookieNumber(1));
    msg.setCurrentMessage(notifyMessage::msgType::BOUGHT_TAP_UPGRADE);
    std::cout << msg;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Cookie Upgrade"), std::string::npos);
    EXPECT_NE(output.find("+1 cookie per tap"), std::string::npos);
}

TEST(notifyMessageTapUpgradeTestSuite, tapUpgradePluralCookies)
{
    testing::internal::CaptureStdout();
    notifyMessage msg;
    msg.setLastItemBoughtName("Pro Cookie");
    msg.setLastItemBoughtAmount(CookieNumber(2));
    msg.setCurrentMessage(notifyMessage::msgType::BOUGHT_TAP_UPGRADE);
    std::cout << msg;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Pro Cookie"), std::string::npos);
    EXPECT_NE(output.find("+2 cookies per tap"), std::string::npos);
}

TEST(notifyMessageTapUpgradeTestSuite, gotCookieSingular)
{
    testing::internal::CaptureStdout();
    notifyMessage msg;
    msg.setLastItemBoughtAmount(CookieNumber(1));
    msg.setCurrentMessage(notifyMessage::msgType::COOKIES_PER_TAP);
    std::cout << msg;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Got 1 cookie!"), std::string::npos);
}

TEST(notifyMessageTapUpgradeTestSuite, gotCookiesPlural)
{
    testing::internal::CaptureStdout();
    notifyMessage msg;
    msg.setLastItemBoughtAmount(CookieNumber(10));
    msg.setCurrentMessage(notifyMessage::msgType::COOKIES_PER_TAP);
    std::cout << msg;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Got 10 cookies!"), std::string::npos);
}

TEST(notifyMessageBoughtItemTestSuite, boughtItemSingularNoS)
{
    testing::internal::CaptureStdout();
    notifyMessage msg;
    msg.setLastItemBoughtName("Cursor");
    msg.setLastItemBoughtAmount(CookieNumber(1));
    msg.setCurrentMessage(notifyMessage::msgType::BOUGHT_ITEM);
    std::cout << msg;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("1 Cursor."), std::string::npos);
}

TEST(notifyMessageBoughtItemTestSuite, boughtItemPluralAddsS)
{
    testing::internal::CaptureStdout();
    notifyMessage msg;
    msg.setLastItemBoughtName("Cursor");
    msg.setLastItemBoughtAmount(CookieNumber(10));
    msg.setCurrentMessage(notifyMessage::msgType::BOUGHT_ITEM);
    std::cout << msg;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("10 Cursors."), std::string::npos);
}
