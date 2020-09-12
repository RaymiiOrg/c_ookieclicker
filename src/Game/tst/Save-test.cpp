#include "GameLoop.h"
#include "Save.h"
#include "gtest/gtest.h"
#include <experimental/filesystem>
#include <memory>

struct SaveTestSuite : public ::testing::Test
{
    std::unique_ptr<Gameloop> game;
    std::unique_ptr<Inventory> inventory = std::make_unique<Inventory>();
    std::unique_ptr<Wallet> wallet = std::make_unique<Wallet>();
    std::unique_ptr<Store> store = std::make_unique<Store>();
    std::unique_ptr<notifyMessage> msg = std::make_unique<notifyMessage>();
    std::unique_ptr<MainView> gamescreen = std::make_unique<MainView>(msg.get(), wallet.get(),
                                                                      inventory.get(), store.get());

    int format1 = 1;
    CookieNumber largeNumber = CookieNumber("354863150980540376871924332068218985606788610769886127757294461121501888");
    std::experimental::filesystem::path current_source_file = std::experimental::filesystem::path(__FILE__);
    std::string testSaveFileFolder = current_source_file.parent_path().string() + "/data/";
    
    
    
    SaveTestSuite()
    {
        std::make_unique<Gameloop>(msg.get(), wallet.get(), inventory.get(),
                                   store.get(), gamescreen.get());
    }
};

TEST_F(SaveTestSuite, saveBlankFile)
{
    //arrange
    auto saveFile = testSaveFileFolder + "saveBlankFile.save";
    auto savegame = Save(saveFile, inventory.get(), wallet.get(), store.get(), format1);
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
    auto savegame = Save(saveFile, inventory.get(), wallet.get(), store.get(), format1);
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
    std::unique_ptr<Inventory> loadinventory = std::make_unique<Inventory>();
    std::unique_ptr<Wallet> loadwallet = std::make_unique<Wallet>();
    std::unique_ptr<Store> loadstore = std::make_unique<Store>();
    std::unique_ptr<notifyMessage> loadmsg = std::make_unique<notifyMessage>();
    std::unique_ptr<MainView> loadgamescreen = std::make_unique<MainView>(loadmsg.get(), loadwallet.get(),
                                                                      loadinventory.get(), loadstore.get());

    //act
    wallet->incrementCookieAmount(CookieNumber(3));
    wallet->incrementCps(CookieNumber(20));
    inventory->addItem("Alchemy Lab", 3);

    inventory->addItem("Grandma", largeNumber);

    auto savegame =  Save(saveFile, inventory.get(), wallet.get(), store.get(), format1);
    auto saveResult = savegame.save();

    std::unique_ptr<Gameloop> gameLoad = std::make_unique<Gameloop>(loadmsg.get(), loadwallet.get(), 
                                                                    loadinventory.get(), loadstore.get(), 
                                                                    loadgamescreen.get());
    auto saveload = Save(saveFile, loadinventory.get(), loadwallet.get(), loadstore.get(), format1);
    auto loadResult = saveload.load();

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

TEST_F(SaveTestSuite, justLoad)
{
    //arrange
    auto saveFile = testSaveFileFolder + "justLoad.save";

    //act
    auto saveload = Save(saveFile, inventory.get(), wallet.get(), store.get(), format1);
    auto loadResult = saveload.load();

    //assert
    ASSERT_EQ(loadResult, true);
    ASSERT_EQ(wallet->getTotalcookies(), 3);
    ASSERT_EQ(wallet->getCps(), 20);
    ASSERT_EQ(inventory->getItemCount("Cursor"), 3);
    ASSERT_EQ(store->getPrice(store->getItemByName("Cursor"), inventory->getItemCount("Cursor")), 23);
    ASSERT_EQ(inventory->getItemCount("Grandma"), largeNumber);
}