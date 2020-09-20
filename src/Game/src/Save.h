//
// Created by remy on 31-05-20.
//

#ifndef C_OOKIECLIKER_SAVE_H
#define C_OOKIECLIKER_SAVE_H

#include "GameLoop.h"
#include <fstream>

class Save
{
public:
    Save(std::string filename, Inventory *Inventory, Wallet *wallet, Store *store, int format);
    bool save();
    bool load();

private:
    std::string saveFileName;
    Inventory *inventory;
    Wallet *wallet;
    Store *store;
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
    void load_step_7_CookiesViaInput(std::vector<std::string> &inV);
    void load_step_6_Items(std::vector<std::string> &inV);

    void save_step_1_Header(std::ofstream &out) const;
    void save_step_2_Format(std::ofstream &out) const;
    void save_step_3_CookieAmount(std::ofstream &out) const;
    void save_step_4_CPS(std::ofstream &out) const;
    void save_step_5_TotalCookies(std::ofstream &out);
    void save_step_6_Items(std::ofstream &out) const;
    void save_step_7_CookiesViaInput(std::ofstream &out);

    int loadAmountOfItems(std::vector<std::string> &inV) const;
};

#endif //C_OOKIECLIKER_SAVE_H
