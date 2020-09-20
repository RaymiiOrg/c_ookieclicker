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
    int getFormat();
    std::vector<std::string> getSaveData();
    bool loadFormatOne();
    bool saveFormatOne();
    bool loadFormatTwo();
    bool saveFormatTwo();
    std::string saveFileName;
    Inventory *m_Inventory;
    Wallet *m_Wallet;
    Store *m_Store;
    int m_Format;

    void resetGameData();

    void loadItems(std::vector<std::string> &inV);

    void saveItems(std::ofstream &out) const;
};

#endif //C_OOKIECLIKER_SAVE_H
