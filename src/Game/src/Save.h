//
// Created by remy on 31-05-20.
//

#ifndef C_OOKIECLIKER_SAVE_H
#define C_OOKIECLIKER_SAVE_H

#include "GameLoop.h"
#include <fstream>

class Save {
public:
    Save(const std::string &filename, const Inventory &Inventory, const Wallet &wallet, int format);
    bool save();
    bool load();

private:
    std::string m_Filename;
    Inventory m_Inventory;
    Wallet m_Wallet;
    int m_Format;

};


#endif //C_OOKIECLIKER_SAVE_H
