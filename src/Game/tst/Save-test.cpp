#include "gtest/gtest.h"
#include <experimental/filesystem>
#include <memory>

#define private public
#include "GameLoop.h"
#include "Save.h"

struct SaveTestSuite : public ::testing::Test
{
    std::unique_ptr<Gameloop> game;
    std::unique_ptr<Inventory> inventory = std::make_unique<Inventory>();
    std::unique_ptr<Wallet> wallet = std::make_unique<Wallet>();
    std::unique_ptr<ItemStore> itemstore = std::make_unique<ItemStore>();
    std::unique_ptr<notifyMessage> msg = std::make_unique<notifyMessage>();
    std::unique_ptr<MainView> gamescreen = std::make_unique<MainView>(msg.get(), wallet.get(), inventory.get(), itemstore.get());

    int format1 = 1;
    int format2 = 2;
    CookieNumber largeNumber = CookieNumber("354863150980540376871924332068218985606788610769886127757294461121501888");
    std::experimental::filesystem::path current_source_file = std::experimental::filesystem::path(__FILE__);
    std::string testSaveFileFolder = current_source_file.parent_path().string() + "/data/";

    SaveTestSuite()
    {
        std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(), itemstore.get(), gamescreen.get());
    }
};

TEST_F(SaveTestSuite, saveBlankFile_v1)
{
    //arrange
    auto saveFile = testSaveFileFolder + "saveBlankFile.save1";
    auto savegame = Save(saveFile, inventory.get(), wallet.get(), itemstore.get(), format1);
    //act
    auto result = savegame.saveFormatOne();
    //assert
    ASSERT_EQ(std::experimental::filesystem::exists(saveFile), true);
    ASSERT_EQ(result, true);
}

TEST_F(SaveTestSuite, loadNonExistentFile)
{
    //arrange
    auto saveFile = testSaveFileFolder + "nonExistentFile.save";
    auto savegame = Save(saveFile, inventory.get(), wallet.get(), itemstore.get(), format1);
    // act
    auto result = savegame.load();
    //assert
    ASSERT_EQ(std::experimental::filesystem::exists(saveFile), false);
    ASSERT_EQ(result, false);
}

TEST_F(SaveTestSuite, saveThenLoad_v1)
{
    //arrange
    auto saveFile = testSaveFileFolder + "saveThenLoad.save1";
    std::unique_ptr<Inventory> loadinventory = std::make_unique<Inventory>();
    std::unique_ptr<Wallet> loadwallet = std::make_unique<Wallet>();
    std::unique_ptr<ItemStore> loadstore = std::make_unique<ItemStore>();
    std::unique_ptr<notifyMessage> loadmsg = std::make_unique<notifyMessage>();
    std::unique_ptr<MainView> loadgamescreen = std::make_unique<MainView>(loadmsg.get(), loadwallet.get(), loadinventory.get(), loadstore.get());

    //act
    wallet->incrementCookieAmount(CookieNumber(3));
    wallet->incrementCps(CookieNumber(20));
    inventory->addItem("Alchemy Lab", 3);

    inventory->addItem("Grandma", largeNumber);

    auto savegame = Save(saveFile, inventory.get(), wallet.get(), itemstore.get(), format1);
    auto saveResult = savegame.saveFormatOne();

    std::unique_ptr<Gameloop> gameLoad = std::make_unique<Gameloop>(loadmsg.get(), loadwallet.get(), loadinventory.get(), loadstore.get(), loadgamescreen.get());
    auto saveload = Save(saveFile, loadinventory.get(), loadwallet.get(), loadstore.get(), format1);
    auto loadResult = saveload.loadFormatOne();

    //assert
    ASSERT_EQ(std::experimental::filesystem::exists(saveFile), true);
    ASSERT_EQ(saveResult, true);
    ASSERT_EQ(loadResult, true);
    ASSERT_EQ(loadwallet->getTotalcookies(), 3);
    ASSERT_EQ(loadwallet->getCps(), 20);
    ASSERT_EQ(loadinventory->getItemCount("Alchemy Lab"), 3);
    ASSERT_EQ(loadstore->getPrice(loadstore->getItemByName("Alchemy Lab"), loadinventory->getItemCount("Alchemy Lab")), 114065625000);
    ASSERT_EQ(loadinventory->getItemCount("Grandma"), largeNumber);
}

TEST_F(SaveTestSuite, justLoad_v1)
{
    //arrange
    auto saveFile = testSaveFileFolder + "justLoad.save1";

    //act
    auto saveload = Save(saveFile, inventory.get(), wallet.get(), itemstore.get(), format1);
    auto loadResult = saveload.loadFormatOne();

    //assert
    ASSERT_EQ(loadResult, true);
    ASSERT_EQ(wallet->getTotalcookies(), 3);
    ASSERT_EQ(wallet->getCps(), 20);
    ASSERT_EQ(inventory->getItemCount("Cursor"), 3);
    ASSERT_EQ(itemstore->getPrice(itemstore->getItemByName("Cursor"), inventory->getItemCount("Cursor")), 23);
    ASSERT_EQ(inventory->getItemCount("Grandma"), largeNumber);
}

TEST_F(SaveTestSuite, getFormat)
{
    //arrange
    auto saveFile = testSaveFileFolder + "justLoad.save1";
    auto saveFile_v2 = testSaveFileFolder + "justLoad.save2";

    //act
    auto saveload = Save(saveFile, inventory.get(), wallet.get(), itemstore.get(), format1);
    auto loadResult = saveload.getFormat();

    auto saveload_v2 = Save(saveFile_v2, inventory.get(), wallet.get(), itemstore.get(), format1);
    auto loadResult_v2 = saveload_v2.getFormat();

    //assert
    ASSERT_EQ(loadResult, 1);
    ASSERT_EQ(loadResult_v2, 2);
}

TEST_F(SaveTestSuite, convertV1toV2)
{
    //arrange
    auto saveFile = testSaveFileFolder + "justLoad.save1";
    auto saveFile_v2 = testSaveFileFolder + "saveConvert_v1_to_v2";

    //act
    auto saveload = Save(saveFile, inventory.get(), wallet.get(), itemstore.get(), format1);
    saveload.loadFormatOne();
    auto firstFormat = saveload.getFormat();

    saveload.saveFileName = saveFile_v2;
    saveload.saveFormatTwo();

    auto convertFormat = saveload.getFormat();

    //assert
    ASSERT_EQ(firstFormat, 1);
    ASSERT_EQ(convertFormat, 2);
}

TEST_F(SaveTestSuite, saveThenLoad_v2)
{
    //arrange
    auto saveFile = testSaveFileFolder + "saveThenLoad.save2";
    std::unique_ptr<Inventory> loadinventory = std::make_unique<Inventory>();
    std::unique_ptr<Wallet> loadwallet = std::make_unique<Wallet>();
    std::unique_ptr<ItemStore> loadstore = std::make_unique<ItemStore>();
    std::unique_ptr<notifyMessage> loadmsg = std::make_unique<notifyMessage>();
    std::unique_ptr<MainView> loadgamescreen = std::make_unique<MainView>(loadmsg.get(), loadwallet.get(), loadinventory.get(), loadstore.get());

    //act
    wallet->incrementCookieAmount(CookieNumber(3));
    wallet->incrementCookieViaInput(CookieNumber(3));
    wallet->incrementCps(CookieNumber(20));
    inventory->addItem("Alchemy Lab", 3);
    inventory->addItem("Grandma", largeNumber);

    auto savegame = Save(saveFile, inventory.get(), wallet.get(), itemstore.get(), format1);
    auto saveResult = savegame.saveFormatTwo();

    std::unique_ptr<Gameloop> gameLoad = std::make_unique<Gameloop>(loadmsg.get(), loadwallet.get(), loadinventory.get(), loadstore.get(), loadgamescreen.get());
    auto saveload = Save(saveFile, loadinventory.get(), loadwallet.get(), loadstore.get(), format2);
    auto loadResult = saveload.loadFormatTwo();

    //assert
    ASSERT_EQ(std::experimental::filesystem::exists(saveFile), true);
    ASSERT_EQ(saveResult, true);
    ASSERT_EQ(loadResult, true);
    ASSERT_EQ(loadwallet->getTotalcookies(), 9);
    ASSERT_EQ(loadwallet->getCps(), 20);
    ASSERT_EQ(loadwallet->getCookiesViaInput(), 3);
    ASSERT_EQ(loadinventory->getItemCount("Alchemy Lab"), 3);
    ASSERT_EQ(loadstore->getPrice(loadstore->getItemByName("Alchemy Lab"), loadinventory->getItemCount("Alchemy Lab")), 114065625000);
    ASSERT_EQ(loadinventory->getItemCount("Grandma"), largeNumber);
}
