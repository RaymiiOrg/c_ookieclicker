#include "gtest/gtest.h"
#include <memory>
#define private public
#include "GameLoop.h"
#include "ItemStore.h"
#include "MainView.h"

struct GameloopTestSuite : public ::testing::Test
{
    std::unique_ptr<Gameloop> game;
    std::unique_ptr<Inventory> inventory = std::make_unique<Inventory>();
    std::unique_ptr<Wallet> wallet = std::make_unique<Wallet>();
    std::unique_ptr<ItemStore> store = std::make_unique<ItemStore>();
    std::unique_ptr<notifyMessage> msg = std::make_unique<notifyMessage>();
    std::unique_ptr<MainView> gamescreen = std::make_unique<MainView>(msg.get(), wallet.get(), inventory.get(), store.get());
    GameloopTestSuite()
    {
        game = std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(), store.get(), gamescreen.get());
    }
};

TEST_F(GameloopTestSuite, incrementCps)
{
    // MainView wires the achievement lists onto the wallet, so reaching 1 cps
    // unlocks the "1 cps" milestone (+1% bonus). Cookies accrue at the effective
    // rate: 1 cps * 1.01 * 1s = 1.01.
    game->wallet->incrementCps(CookieNumber(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    game->incrementCookiesOnTime();
    EXPECT_EQ(game->wallet->getCookieAmount(), CookieNumber("1.01"));
}

TEST_F(GameloopTestSuite, incrementCpsLargerAmount)
{
    // 3500 cps unlocks the 1/10/100/1000 cps milestones (4 * 1% = +4% bonus).
    // Cookies accrue at the effective rate: 3500 cps * 1.04 * 3s = 10920.
    game->wallet->incrementCps(CookieNumber(3500));
    std::this_thread::sleep_for(std::chrono::seconds(3));
    game->incrementCookiesOnTime();
    EXPECT_EQ(game->wallet->getCookieAmount(), CookieNumber(10920));
}

TEST_F(GameloopTestSuite, firstCookieShowsCookieAndAchievementTogether)
{
    // Tapping the first cookie both grants a cookie and unlocks the
    // "Wake and bake" (1 cookie) achievement; both notices must be shown.
    game->handleCookieOrQuitChoice(game::cookieKey);

    testing::internal::CaptureStdout();
    std::cout << *msg;
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Got 1 cookie!"), std::string::npos);
    EXPECT_NE(output.find("Achievement unlocked"), std::string::npos);
}

TEST_F(GameloopTestSuite, spammingCookieKeyCountsOncePerLine)
{
    // Typing "cccc" on one line must only grant a single cookie.
    game->processInputLine("cccc");
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(1));
}

TEST_F(GameloopTestSuite, singleCookieKeyGrantsOneCookie)
{
    game->processInputLine("c");
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(1));
}

TEST_F(GameloopTestSuite, separateLinesEachGrantACookie)
{
    game->processInputLine("c");
    game->processInputLine("c");
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(2));
}

TEST_F(GameloopTestSuite, cookieAmongOtherKeysStillCountsOnce)
{
    // The cookie still registers once even mixed with other keystrokes.
    game->processInputLine("1c2c");
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(1));
}

TEST_F(GameloopTestSuite, resetClearsProgress)
{
    game->processInputLine("c");
    game->wallet->incrementCps(CookieNumber(5));
    game->reset();
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(0));
    EXPECT_EQ(wallet->getCps(), CookieNumber(0));
}

#ifndef NDEBUG
TEST_F(GameloopTestSuite, debugKeySevenGrantsCookiesAndTaps)
{
    game->processInputLine("7");
    // +100 cookies, then incrementCookieViaInput(100) adds another 100.
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(200));
    EXPECT_EQ(inventory->getCookiesPerTap(), CookieNumber(10));
}

TEST_F(GameloopTestSuite, debugKeyEightDoublesCookies)
{
    wallet->incrementCookieAmount(CookieNumber(50));
    game->processInputLine("8"); // adds double the current amount: 50 + 50*2
    EXPECT_EQ(wallet->getCookieAmount(), CookieNumber(150));
}
#endif

TEST_F(GameloopTestSuite, renderScreenProducesOutput)
{
    testing::internal::CaptureStdout();
    game->renderScreenIfOutputChanged();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST_F(GameloopTestSuite, quitStopsAndShowsFinalScore)
{
    testing::internal::CaptureStdout();
    game->quit();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Well done."), std::string::npos);
}

TEST_F(GameloopTestSuite, laterCookieTapShowsOnlyCookieNotice)
{
    // Once the 1-cookie achievement is already unlocked, a subsequent tap shows
    // just the cookie notice — the stale achievement message is replaced.
    game->handleCookieOrQuitChoice(game::cookieKey);
    game->handleCookieOrQuitChoice(game::cookieKey);

    testing::internal::CaptureStdout();
    std::cout << *msg;
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Got 1 cookie!"), std::string::npos);
    EXPECT_EQ(output.find("Achievement unlocked"), std::string::npos);
}

//TEST_F(GameloopTestSuite, maxItemAmount)
//{
//    //arrange
//    auto game0 = std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(),
//                                            store.get(), gamescreen.get());
//    auto game1 = std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(),
//                                            store.get(), gamescreen.get());
//    auto game2 = std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(),
//                                            store.get(), gamescreen.get());
//    auto game3 = std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(),
//                                            store.get(), gamescreen.get());
//    auto game4 = std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(),
//                                            store.get(), gamescreen.get());
//
//    //act
//    game0->wallet->incrementCookieAmount(CookieNumber(15));
//
//    game1->wallet->incrementCookieAmount(CookieNumber(15 + 18));
//
//    game2->wallet->incrementCookieAmount(CookieNumber(8));
//
//    game3->wallet->incrementCookieAmount(CookieNumber(370));
//    game3->inventory->addItem("Cursor", 1);
//
//    game4->wallet->incrementCookieAmount(CookieNumber(5000));
//    game4->inventory->addItem("Cursor", 1);
//
//    //assert
//    auto result0 = game0->maxItemAmount(game1->store->getItemByName("Cursor"));
//    auto result1 = game1->maxItemAmount(game1->store->getItemByName("Cursor"));
//    auto result2 = game2->maxItemAmount(game2->store->getItemByName("Cursor"));
//    auto result3 = game3->maxItemAmount(game3->store->getItemByName("Cursor"));
//    auto result4 = game4->maxItemAmount(game4->store->getItemByName("Cursor"));
//
//    EXPECT_EQ(result0, 1);
//    EXPECT_EQ(result1, 2);
//    EXPECT_EQ(result2, 0);
//    EXPECT_EQ(result3, 10);
//    EXPECT_EQ(result4, 27);
//}

TEST_F(GameloopTestSuite, reset)
{
    //arrange
    game->wallet->incrementCookieAmount(CookieNumber(10));
    game->wallet->incrementCookieAmount(CookieNumber(20));
    game->wallet->incrementCps(CookieNumber(100));
    game->inventory->addItem("Cursor", 30);
    game->inventory->addItem("Grandma", 1);

    //act
    game->reset();

    //assert
    EXPECT_EQ(game->wallet->getCps(), 0);
    EXPECT_EQ(game->wallet->getTotalcookies(), 0);
    EXPECT_EQ(game->wallet->getCookieAmount(), 0);
    EXPECT_EQ(game->inventory->getItemCount("Cursor"), 0);
    EXPECT_EQ(game->inventory->getItemCount("Grandma"), 0);
    EXPECT_EQ(game->inventory->getLastItemAdded().empty(), true);
}