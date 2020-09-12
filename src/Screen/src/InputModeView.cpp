//
// Created by remy on 08-09-20.
//

#include "InputModeView.h"
#include "terminalCodes.h"

void InputModeView::render()
{
    std::cout << escapeCode.cursorTo6x0;
    for (int line = 0; line < 150; ++line)
        std::cout << escapeCode.cursorDownOneLine << escapeCode.eraseCurrentLine;
    std::cout << escapeCode.cursorTo6x0;
    std::cout << escapeCode.terminalBold;
    std::cout << "[c]\t:\t get cookie \n";
    std::cout << escapeCode.terminalReset;
    inputBar();
}

void InputModeView::handleInput(const std::string &input)
{
}

void InputModeView::inputBar()
{
    int count = 1;
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