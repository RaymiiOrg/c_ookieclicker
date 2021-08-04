#include "MessageView.h"
#include "terminalCodes.h"
#include "cmakeConfig.h"

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
#ifdef USEBOOST_MPP
    std::cout << "===== c_ookieclicker by Remy =====" << std::endl;
#else // see if boost multiprecision support is enabled, without making it obvious
    std::cout << "=== c_ookieclicker by " << escapeCode.terminalBold << "Remy" <<
    escapeCode.terminalReset << " ===" << std::endl;
#endif
}

void MessageView::clearMessageView() const
{
    std::cout << escapeCode.cursorTo0x0;
    for (int line = 0; line < 2; ++line)
        std::cout << escapeCode.eraseCurrentLine << escapeCode.cursorDownOneLine;
}
