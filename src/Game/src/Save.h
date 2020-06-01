//
// Created by remy on 31-05-20.
//

#ifndef C_OOKIECLIKER_SAVE_H
#define C_OOKIECLIKER_SAVE_H

#include "GameLoop.h"
#include <fstream>

class Save {
public:
    Save(const std::string &mFilename, const Inventory &mInventory, const Wallet &mWallet, int mFormat);
    bool save();
    bool load();

private:
    std::string m_Filename;
    Inventory m_Inventory;
    Wallet m_Wallet;
    int m_Format;

};


#endif //C_OOKIECLIKER_SAVE_H
