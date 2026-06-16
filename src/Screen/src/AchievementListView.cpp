#include "AchievementListView.h"
#include "terminalCodes.h"
void AchievementListView::render()
{
    listAchievementViews();
    renderBonusSummary();
    if (activeView != nullptr)
        activeView->render();
}

void AchievementListView::renderBonusSummary() const
{
    if (walletReader == nullptr)
        return;

    CookieNumber bonus = walletReader->getAchievementBonusMultiplier();
    CookieNumber bonusPct = bonus * CookieNumber(100);
    CookieNumber bonusCps = walletReader->getCps() * bonus;

    std::cout << "Achievement bonus: +" << cp.print(bonusPct) << "% cps";
    if (bonusCps > CookieNumber(0))
        std::cout << " (+" << cp.print(bonusCps) << " cps)";
    std::cout << std::endl;
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
            if (inputKey == game::cookieKey.at(0))
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
    // skip c, it's get cookie input key. this code is a reminder.
    if (input == "d")
        activeView = &cookiesViaInputView;
}

const std::string &AchievementListView::name()
{
    return _name;
}

AchievementListView::AchievementListView(Subject *walletSubject, IWalletReader *walletReader, notifyMessage *msg) :
    walletSubject(walletSubject), walletReader(walletReader), msg(msg)
{
    createAchievementView(&cookieAmountAchievementList, &cookieAmountAchievementView, AchievementRepository::getCookieAmountMilestones());
    createAchievementView(&cookiesPerSecondAchievementList, &cookiesPerSecondView, AchievementRepository::getCookiesPerSecondMilestones());
    createAchievementView(&cookiesViaInputAchievementList, &cookiesViaInputView, AchievementRepository::getCookiesViaInputMilestones());
}
