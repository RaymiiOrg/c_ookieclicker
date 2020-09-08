//
// Created by remy on 08-09-20.
//

#include "MessageView.h"
#include "terminalCodes.h"

void MessageView::render() {
    std::cout << escapeCode.cursorTo0x0;
    for (int line = 0; line < 2; ++line)
        std::cout << escapeCode.eraseCurrentLine << escapeCode.cursorDownOneLine;
    std::cout << escapeCode.cursorTo0x0;
    std::cout << escapeCode.eraseCurrentLine;
    std::cout << "===== c_ookieclicker by Remy ====" << std::endl;
    std::cout << escapeCode.eraseCurrentLine;
    if (msg.getCurrentMessage() != notifyMessage::msgType::NO_MSG) {
        std::cout << escapeCode.terminalBold;
        std::cout << msg;
        std::cout << escapeCode.terminalReset;
    }
    std::cout << std::endl;

}
