#include <memory>
#include <experimental/filesystem>
#include "gtest/gtest.h"
#include "GameLoop.h"
#include "Save.h"

struct SaveTestSuite : public ::testing::Test
{
    std::unique_ptr<Gameloop> game;
    int format1 = 1;
    CookieNumber largeNumber = CookieNumber("354863150980540376871924332068218985606788610769886127757294461121501888");
    std::experimental::filesystem::path current_source_file = std::experimental::filesystem::path(__FILE__);
    std::string testSaveFileFolder = current_source_file.parent_path().string() + "/data/";
    SaveTestSuite()
    {
        game = std::make_unique<Gameloop>(false);
    }
};

TEST_F(SaveTestSuite, saveBlankFile)
{
    //arrange
    auto saveFile = testSaveFileFolder + "saveBlankFile.save";
    auto savegame = Save(saveFile, game->getInventory(), game->getWallet(), game->getStore(), format1);
    //act
    auto result = savegame.save();
    //assert
    ASSERT_EQ(std::experimental::filesystem::exists(saveFile), true);
    ASSERT_EQ(result, true);
}

TEST_F(SaveTestSuite, loadNonExistentFile)
{
    //arrange
    auto saveFile = testSaveFileFolder + "nonExistentFile.save";
    auto savegame = Save(saveFile, game->getInventory(), game->getWallet(), game->getStore(), format1);
    // act
    auto result = savegame.load();
    //assert
    ASSERT_EQ(std::experimental::filesystem::exists(saveFile), false);
    ASSERT_EQ(result, false);
}

TEST_F(SaveTestSuite, saveThenLoad)
{
    //arrange
    auto saveFile = testSaveFileFolder + "saveThenLoad.save";

    //act
    game->getWallet().incrementCookieAmount(CookieNumber(3));
    game->getWallet().incrementCps(CookieNumber(20));
    game->getInventory().addItem("Cursor", 3);

    game->getInventory().addItem("Grandma", largeNumber);

    auto savegame = Save(saveFile, game->getInventory(), game->getWallet(), game->getStore(), format1);
    auto saveResult = savegame.save();

    std::unique_ptr<Gameloop> gameLoad = std::make_unique<Gameloop>(false);
    auto saveload = Save(saveFile, gameLoad->getInventory(), gameLoad->getWallet(), gameLoad->getStore(), format1);
    auto loadResult = saveload.load();

    //assert
    ASSERT_EQ(std::experimental::filesystem::exists(saveFile), true);
    ASSERT_EQ(saveResult, true);
    ASSERT_EQ(loadResult, true);
    ASSERT_EQ(gameLoad->getWallet().getTotalcookies(), 3);
    ASSERT_EQ(gameLoad->getWallet().getCps(), 20);
    ASSERT_EQ(gameLoad->getInventory().getItemCount("Cursor"), 3);
    ASSERT_EQ(gameLoad->getStore().getPrice(gameLoad->getStore().getItemByName("Cursor"),
                                            gameLoad->getInventory().getItemCount("Cursor")), 23);
    ASSERT_EQ(gameLoad->getInventory().getItemCount("Grandma"), largeNumber);
}

TEST_F(SaveTestSuite, justLoad)
{
    //arrange
    auto saveFile = testSaveFileFolder + "justLoad.save";

    //act
    auto saveload = Save(saveFile, game->getInventory(), game->getWallet(), game->getStore(), format1);
    auto loadResult = saveload.load();

    //assert
    ASSERT_EQ(loadResult, true);
    ASSERT_EQ(game->getWallet().getTotalcookies(), 3);
    ASSERT_EQ(game->getWallet().getCps(), 20);
    ASSERT_EQ(game->getInventory().getItemCount("Cursor"), 3);
    ASSERT_EQ(game->getStore().getPrice(game->getStore().getItemByName("Cursor"), game->getInventory().getItemCount("Cursor")), 23);
    ASSERT_EQ(game->getInventory().getItemCount("Grandma"), largeNumber);
}