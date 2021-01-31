#include "MessageView.h"
#include "terminalCodes.h"

void MessageView::render()
{
    clearMessageView();
    showGameTitle();
    showMessage();
}

void MessageView::showMessage() const
{
    std::cout << escapeCode.eraseCurrentLine;
    std::cout << escapeCode.terminalBold;
    if (msg != nullptr)
        std::cout << *msg;
    std::cout << escapeCode.terminalReset;
    std::cout << std::endl;
}

void MessageView::showGameTitle() const
{
    std::cout << escapeCode.cursorTo0x0;
    std::cout << escapeCode.eraseCurrentLine;
    std::cout << "===== c_ookieclicker by Remy ====" << std::endl;
}

void MessageView::clearMessageView() const
{
    std::cout << escapeCode.cursorTo0x0;
    for (int line = 0; line < 2; ++line)
        std::cout << escapeCode.eraseCurrentLine << escapeCode.cursorDownOneLine;
}
