#include "InputModeView.h"
#include "CookieNumbers.h"
#include "terminalCodes.h"

void InputModeView::render()
{
    clearLines();
    renderGetCookie();
    inputBar();
}

void InputModeView::renderGetCookie() const
{
    CookieNumber perTap = (cookieStats != nullptr) ? cookieStats->getCookiesPerTap() : CookieNumber(1);
    std::string noun = (perTap == CookieNumber(1)) ? "cookie" : "cookies";
    std::cout << escapeCode.cursorTo6x0;
    std::cout << escapeCode.eraseCurrentLine;
    std::cout << escapeCode.terminalBold;
    std::cout << "[c]\t:\t get " << cp.print(perTap) << " " << noun << "\n";
    std::cout << escapeCode.terminalReset;
}

void InputModeView::clearLines()
{
    std::cout << escapeCode.cursorTo6x0;
    for (int line = 0; line < 150; ++line)
        std::cout << escapeCode.cursorDownOneLine << escapeCode.eraseCurrentLine;
}

void InputModeView::handleInput(const std::string &input)
{
}

void InputModeView::inputBar()
{
    size_t count = 1;
    for (View *view : allviews)
    {
        if (view != nullptr)
        {
            if (view == currentActiveView)
                std::cout << escapeCode.terminalBold;
            std::cout << "[" << count << "]: " << view->name();
            if (count != allviews.size())
                std::cout << " | ";
            if (view == currentActiveView)
                std::cout << escapeCode.terminalReset;

            ++count;
        }
    }
}