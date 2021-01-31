#include "AchievementListView.h"
#include "terminalCodes.h"
void AchievementListView::render()
{
    listAchievementViews();
    if (activeView != nullptr)
        activeView->render();
}

void AchievementListView::listAchievementViews() const
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

void AchievementListView::handleInput(const std::string &input)
{
    if (input == "a")
        activeView = &cookieAmountAchievementView;
    if (input == "b")
        activeView = &cookiesPerSecondView;
    if (input == "d") // skip c, it's get cookie input key. this code is a reminder.
        activeView = &cookiesViaInputView;
}

const std::string &AchievementListView::name()
{
    return _name;
}

AchievementListView::AchievementListView(Wallet *wallet, notifyMessage *msg) :
    wallet(wallet), msg(msg)
{
    createAchievementView(&cookieAmountAchievementList, &cookieAmountAchievementView, "/gamedata/achievements/CookieAmountAchievements.csv");
    createAchievementView(&cookiesPerSecondAchievementList, &cookiesPerSecondView, "/gamedata/achievements/CookiesPerSecondAchievements.csv");
    createAchievementView(&cookiesViaInputAchievementList, &cookiesViaInputView, "/gamedata/achievements/CookiesViaInputAchievements.csv");
}
