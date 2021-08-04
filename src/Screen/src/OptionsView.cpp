#include "OptionsView.h"
#include "CookieNumbers.h"
#include "Game/src/Save.h"
#include "cmakeConfig.h"
#include <limits>

void OptionsView::render()
{
    std::cout << "\n===== Options ====\n";

    std::cout << "[q]: quit; \n";
    std::cout << "[s]: save; \n";
    std::cout << "[l]: load; \n";
    std::cout << std::endl;
    std::cout << "version: " << game::gameVersion << " ";
#ifdef PACKAGE_GITSHA
    std::cout << " (commit " << std::string(PACKAGE_GITSHA) << ")";
#endif
#ifdef USEBOOST_MPP
    std::cout << " (With Boost Multiprecision) ";
#else
    std::cout << escapeCode.terminalBold << " \nWithout Boost Multiprecision, "
                 "strange things will happen when numbers get bigger than \n";
    printf("%.10Le", std::numeric_limits<long double>::max());
    std::cout << ")\n" << escapeCode.terminalReset;
#endif
    std::cout << std::endl;
}

void OptionsView::handleInput(const std::string &input)
{
    if (input == "s")
    {
        save();
    }
    else if (input == "l")
    {
        load();
    }
}

void OptionsView::load()
{
    if (inventory && wallet && store && msg)
    {
        auto saveGame = Save(savefilename, inventory, wallet, store, 2);
        if (saveGame.load())
        {
            msg->setCurrentMessage(notifyMessage::msgType::LOADED);
        }
    }
    else
    {
        msg->setLastError("Could not load game, nullptrs found");
        msg->setCurrentMessage(notifyMessage::msgType::ERROR);
    }
}

void OptionsView::save()
{
    if (inventory && wallet && store && msg)
    {
        auto saveGame = Save(savefilename, inventory, wallet, store, 2);
        if (saveGame.save())
        {
            msg->setCurrentMessage(notifyMessage::msgType::SAVED);
        }
    }
    else
    {
        msg->setLastError("Could not save game, nullptrs found");
        msg->setCurrentMessage(notifyMessage::msgType::ERROR);
    }
}
