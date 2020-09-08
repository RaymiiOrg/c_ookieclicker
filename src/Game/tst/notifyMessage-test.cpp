#include "notifyMessage.h"
#include "gtest/gtest.h"

TEST(notifyMessageTestSuite, setMessage)
{
    //arrange
    notifyMessage msg;

    //act
    msg.setCurrentMessage(notifyMessage::msgType::SAVED);

    //assert
    ASSERT_EQ(msg.getCurrentMessage(), notifyMessage::msgType::SAVED);
}
