//
// Created by remy on 31-05-20.
//

#ifndef C_OOKIECLIKER_SAVE_H
#define C_OOKIECLIKER_SAVE_H

#include "GameLoop.h"
#include <fstream>

class Save {
public:
    Save(std::string filename, Inventory* Inventory, Wallet* wallet, Store *store, int format);
    bool save();
    bool load();

private:
    bool loadFormatOne();
    bool saveFormatOne();
    std::string m_Filename;
    Inventory* m_Inventory;
    Wallet* m_Wallet;
    Store* m_Store;
    int m_Format;
};


#endif //C_OOKIECLIKER_SAVE_H
