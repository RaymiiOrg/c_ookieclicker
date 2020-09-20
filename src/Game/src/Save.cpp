//
// Created by remy on 31-05-20.
//

#include "Save.h"

Save::Save(std::string filename, Inventory *Inventory, Wallet *wallet, Store *store, int format) :
        saveFileName(std::move(
        filename)),
        m_Inventory(Inventory), m_Wallet(wallet), m_Store(store), m_Format(format) {}

bool Save::save()
{
    if (m_Inventory && m_Wallet && m_Format)
        return saveFormatTwo();
    else
        return false;
}

bool Save::load()
{
    if (!m_Inventory || !m_Wallet || !m_Format)
        return false;

    switch (getFormat()) {
        case 1:     return loadFormatOne();
        case 2:     return loadFormatTwo();
        default:    return false;
    }

}

bool Save::saveFormatOne()
{
    std::ofstream out(saveFileName);
    if (out.fail())
        return false;

    out << "# c_ookieClicker savegame, by https://raymii.org"
        << ";";
    out << std::to_string(m_Format) << ";";

    out << m_Wallet->getCookieAmount().str(0, std::ios_base::fixed) << ";";
    out << m_Wallet->getCps().str(0, std::ios_base::fixed) << ";";
    out << m_Wallet->getTotalcookies().str(0, std::ios_base::fixed) << ";";

    saveItems(out);
    return true;
}

void Save::saveItems(std::ofstream &out) const {
    out << m_Inventory->getInventory().size() << ";";
    for (const auto &item : m_Inventory->getInventory())
    {
        out << item.first << "," << item.second.str(0, std::ios_base::fixed) << ";";
    }
}

bool Save::loadFormatOne()
{
    auto inV = getSaveData();
    if (inV.empty())
        return false;

    resetGameData();

    //    for (auto & count : inV) {
    //        std::cout << count << "\n";
    //    }

    m_Wallet->setCookieAmount(CookieNumber(inV.at(2)));
    m_Wallet->setCps(CookieNumber(inV.at(3)));
    m_Wallet->setTotalcookies(CookieNumber(inV.at(4)));

    loadItems(inV);

    return true;
}

void Save::loadItems(std::vector<std::string> &inV) {
    int amountOfItems = std::stoi(inV.at(5));
    if (amountOfItems > 0)
    {
        for (int i = 0; i < amountOfItems; ++i)
        {
            std::string current_item_line;
            std::vector<std::string> in_items;
            std::istringstream itemstream(inV.at(6 + i));
            while (std::getline(itemstream, current_item_line, ','))
            {
                in_items.push_back(current_item_line);
            }
            auto itemName = in_items.front();
            auto itemAmount = CookieNumber(in_items.back());
            m_Inventory->addItem(itemName, itemAmount);
        }
    }
}

void Save::resetGameData() {
    m_Wallet->reset();
    m_Inventory->reset();
    m_Store->reset();
}

bool Save::loadFormatTwo() {
    return false;
}

bool Save::saveFormatTwo() {
    return false;
}

int Save::getFormat() {
        auto inV = getSaveData();
        if (inV.empty())
            return 0;

        if (std::stoi(inV.at(1)) > 0)
            return std::stoi(inV.at(1));

        return 0;
}

std::vector<std::string> Save::getSaveData() {
    std::ifstream in(saveFileName);
    std::vector<std::string> inV;
    if (!in.good())
        return inV;

    std::string current_line;
    while (std::getline(in, current_line, ';'))
    {
        inV.push_back(current_line);
    }
    return inV;
}
