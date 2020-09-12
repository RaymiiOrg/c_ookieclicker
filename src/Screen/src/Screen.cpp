#include "Screen.h"

void Screen::handleInput(const std::string &input)
{
    statusview.handleInput(input);
    switchActiveView(input);
    activeView->handleInput(input);
}

void Screen::switchActiveView(const std::string &input)
{
    if (input == "1")
    {
        activeView = dynamic_cast<View *>(&storeview);
    }
    if (input == "2")
    {
        activeView = dynamic_cast<View *>(&inventoryview);
    }
    if (input == "3")
    {
        activeView = dynamic_cast<View *>(&achievementlistview);
    }
    if (input == "4")
    {
        activeView = dynamic_cast<View *>(&optionsview);
    }
    inputmodeview.setCurrentActiveView(activeView);
}

void Screen::render()
{
    messageview.render();
    statusview.render();
    inputmodeview.render();
    std::cout << std::endl;
    if (activeView)
    {
        activeView->render();
    }
    else
    {
        std::cout << "Loading Active View..." << std::endl;
    }
}
