//
// Created by remy on 08-09-20.
//

#include "StoreView.h"

void StoreView::render()
{
    listViews();
    if(activeView)
        activeView->render();

}

void StoreView::handleInput(const std::string &input)
{
    if (input == "a")
        activeView = &oneItem;
    if (input == "b")
        activeView = &tenItems;
    if (input == "d")
        activeView = &hundredItems;
    if (activeView)
        activeView->handleInput(input);
}


void StoreView::listViews() const
{
    char inputKey = 'a';
    int count = 1;
    for (auto view : allviews)
    {
        if (view != nullptr)
        {
            if (view == activeView)
                std::cout << escapeCode.terminalBold;

            std::cout << "[" << inputKey << "]: " << view->name();

            if (view == activeView)
                std::cout << escapeCode.terminalReset;

            if (count % 3 == 0)
                std::cout << std::endl;
            else
                std::cout << " | ";

            ++inputKey;
            if (inputKey == getCookieInputKey)
                ++inputKey;
            ++count;
        }
    }
    std::cout << std::endl;
}