//
// Created by remy on 31-05-20.
//

#include "Save.h"

Save::Save(std::string filename, Inventory &Inventory, Wallet &wallet, Store &store, int format) : m_Filename(std::move(
        filename)), m_Inventory(Inventory), m_Wallet(wallet), m_Store(store), m_Format(format) {}


bool Save::save() {
    return saveFormatOne();
}

bool Save::load() {
    return loadFormatOne();
}

bool Save::saveFormatOne() {
    std::ofstream out(m_Filename);
    if (out.fail())
        return false;

    out << "# c_ookieClicker savegame, by https://raymii.org" << ";";
    out << std::to_string(m_Format) << ";";

    out << m_Wallet.getCookieAmount().str(0, std::ios_base::fixed) << ";";
    out << m_Wallet.getCps().str(0, std::ios_base::fixed) << ";";
    out << m_Wallet.getTotalcookies().str(0, std::ios_base::fixed) << ";";

    out << m_Inventory.getInventory().size() << ";";
    for (const auto& item : m_Inventory.getInventory())
    {
        out << item.first << "," << item.second.str(0, std::ios_base::fixed) << ";";
    }
    return true;
}

bool Save::loadFormatOne() {
    std::ifstream in(m_Filename);
    std::vector<std::string> inV;
    if (!in.good()) {
        return false;
    }
    m_Wallet.reset();
    m_Inventory.reset();
    m_Store.reset();

    std::string current_line;
    while (std::getline(in, current_line, ';')) {
        inV.push_back(current_line);
    }

//    for (auto & count : inV) {
//        std::cout << count << "\n";
//    }

    m_Wallet.setCookieAmount(CookieNumber(inV.at(2)));
    m_Wallet.setCps(CookieNumber(inV.at(3)));
    m_Wallet.setTotalcookies(CookieNumber(inV.at(4)));

    int amountOfItems = std::stoi(inV.at(5));
    if (amountOfItems > 0) {
        for (int i = 0; i < amountOfItems; ++i) {
            std::string current_item_line;
            std::vector<std::string> in_items;
            std::istringstream itemstream(inV.at(6 + i));
            while (std::getline(itemstream, current_item_line, ',')) {
                in_items.push_back(current_item_line);
            }
            auto itemName = in_items.front();
            auto itemAmount = CookieNumber(in_items.back());
            m_Inventory.addItem(itemName, itemAmount);
        }
    }

    return true;
}
