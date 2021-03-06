#ifndef C_OOKIECLIKER_SAVE_H
#define C_OOKIECLIKER_SAVE_H

#include "GameLoop.h"
#include <fstream>

class Save
{
public:
    Save(std::string filename, Inventory *Inventory, Wallet *wallet, ItemStore *store, int format);
    bool save();
    bool load();

private:
    std::string saveFileName;
    Inventory *inventory;
    Wallet *wallet;
    ItemStore *itemstore;
    int format;

    int getFormat();
    std::vector<std::string> getSaveData();
    bool loadFormatOne();
    bool saveFormatOne();
    bool loadFormatTwo();
    bool saveFormatTwo();
    void resetGameData();

    void load_step_3_CookieAmount(std::vector<std::string> &inV);
    void load_step_4_CPS(std::vector<std::string> &inV);
    void load_step_5_TotalCookies(std::vector<std::string> &inV);
    void load_step_6_Items(std::vector<std::string> &inV);
    void load_step_7_CookiesViaInput(std::vector<std::string> &inV);
    void load_step_8_CookiesPerTap(std::vector<std::string> &inV);

    static void save_step_1_Header(std::ofstream &out) ;
    void save_step_2_Format(std::ofstream &out) const;
    void save_step_3_CookieAmount(std::ofstream &out) const;
    void save_step_4_CPS(std::ofstream &out) const;
    void save_step_5_TotalCookies(std::ofstream &out);
    void save_step_6_Items(std::ofstream &out) const;
    void save_step_7_CookiesViaInput(std::ofstream &out);
    void save_step_8_CookiesPerTap(std::ofstream &out);

    static int loadAmountOfItems(std::vector<std::string> &inV) ;
};

#endif //C_OOKIECLIKER_SAVE_H
