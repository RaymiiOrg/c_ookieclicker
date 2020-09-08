#include "gtest/gtest.h"
#define private public
#include "notifyMessage.h"

TEST(notifyMessageTestSuite, setMessage)
{
    //arrange
    notifyMessage msg;

    //act
    msg.setCurrentMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);

    //assert
    ASSERT_EQ(msg.getCurrentMessage(), notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
}

TEST(notifyMessageTestSuite, getMessage)
{
    //arrange
    testing::internal::CaptureStdout();
    notifyMessage msg;

    //act
    msg.setLastAchievement("testBla");
    msg.setCurrentMessage(notifyMessage::msgType::ACHIEVEMENT_UNLOCKED);
    std::cout << msg;

    //assert
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, msg.lastMessageTime + ": Achievement unlocked: testBla!");
}