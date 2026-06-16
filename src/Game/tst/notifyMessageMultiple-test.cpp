#include "gtest/gtest.h"
#define private public
#include "notifyMessage.h"

/** Captures the rendered output of a notifyMessage. */
static std::string render(notifyMessage &msg)
{
    testing::internal::CaptureStdout();
    std::cout << msg;
    return testing::internal::GetCapturedStdout();
}

TEST(notifyMessageMultipleTestSuite, addMessageOnEmptyShowsSingle)
{
    notifyMessage msg;
    msg.setLastItemBoughtAmount(CookieNumber(1));
    msg.addMessage(notifyMessage::msgType::COOKIES_PER_TAP);
    EXPECT_NE(render(msg).find("Got 1 cookie!"), std::string::npos);
}

TEST(notifyMessageMultipleTestSuite, firstCookieShowsBothCookieAndAchievement)
{
    // Mirrors the first-tap flow: the "got a cookie" notice is shown, then the
    // achievement unlocked by that same tap appends alongside it.
    notifyMessage msg;
    msg.setLastItemBoughtAmount(CookieNumber(1));
    msg.setCurrentMessage(notifyMessage::msgType::COOKIES_PER_TAP);
    msg.setLastAchievement("Wake and bake");
    msg.addMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);

    std::string output = render(msg);
    EXPECT_NE(output.find("Got 1 cookie!"), std::string::npos);
    EXPECT_NE(output.find("Achievement unlocked: Wake and bake!"), std::string::npos);
}

TEST(notifyMessageMultipleTestSuite, multipleAchievementsAllShown)
{
    notifyMessage msg;
    msg.setLastAchievement("Wake and bake");
    msg.addMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
    msg.setLastAchievement("Making some dough");
    msg.addMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);

    std::string output = render(msg);
    EXPECT_NE(output.find("Wake and bake!"), std::string::npos);
    EXPECT_NE(output.find("Making some dough!"), std::string::npos);
}

TEST(notifyMessageMultipleTestSuite, separatorBetweenMultipleMessages)
{
    notifyMessage msg;
    msg.setLastItemBoughtAmount(CookieNumber(1));
    msg.setCurrentMessage(notifyMessage::msgType::COOKIES_PER_TAP);
    msg.setLastAchievement("Wake and bake");
    msg.addMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
    EXPECT_NE(render(msg).find(" | "), std::string::npos);
}

TEST(notifyMessageMultipleTestSuite, setCurrentMessageReplacesPrevious)
{
    notifyMessage msg;
    msg.setLastAchievement("Wake and bake");
    msg.addMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
    // A new standalone message clears the earlier achievement notice.
    msg.setCurrentMessage(notifyMessage::msgType::SAVED);

    std::string output = render(msg);
    EXPECT_NE(output.find("Game saved."), std::string::npos);
    EXPECT_EQ(output.find("Achievement unlocked"), std::string::npos);
}

TEST(notifyMessageMultipleTestSuite, setCurrentMessageKeepsSingleAfterAppends)
{
    notifyMessage msg;
    msg.setLastAchievement("A");
    msg.addMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
    msg.setLastAchievement("B");
    msg.addMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
    msg.setCurrentMessage(notifyMessage::msgType::SAVED);
    EXPECT_EQ(msg._messages.size(), 1u);
}

TEST(notifyMessageMultipleTestSuite, emptyByDefaultPrintsNothing)
{
    notifyMessage msg;
    EXPECT_EQ(render(msg), "");
}

TEST(notifyMessageMultipleTestSuite, getCurrentMessageReflectsLastAdded)
{
    notifyMessage msg;
    msg.setLastItemBoughtAmount(CookieNumber(1));
    msg.setCurrentMessage(notifyMessage::msgType::COOKIES_PER_TAP);
    msg.setLastAchievement("Wake and bake");
    msg.addMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
    EXPECT_EQ(msg.getCurrentMessage(), notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
}
