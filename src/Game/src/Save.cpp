//
// Created by remy on 31-05-20.
//

#include "Save.h"

Save::Save(const std::string &filename, const Inventory &Inventory, const Wallet &wallet, int format) : m_Filename(
        filename), m_Inventory(Inventory), m_Wallet(wallet), m_Format(format) {}

bool Save::save() {
    std::ofstream out(m_Filename);
    if (out.fail())
        return false;

    out << "# c_ookieClicker savegame, by https://raymii.org" << ";";
    out << std::to_string(m_Format) << ";";

    out << m_Wallet.getCookieAmount() << ";";
    out << m_Wallet.getCps() << ";";
    out << m_Wallet.getTotalcookies() << ";";

    out << m_Inventory.getInventory().size() << ";";
    for (const auto& item : m_Inventory.getInventory())
    {
        out << item.first.name << " " << item.second << " " << item.first.price << ";";
    }
    return true;
}

bool Save::load() {
    std::ifstream in(m_Filename);
    std::vector<std::string> inV;
    if (!in.good()) {
        return false;
    }
    std::string current_line;
    while (std::getline(in, current_line, ';')) {
        inV.push_back(current_line);
    }

    for (auto & count : inV) {
        std::cout << count << "\n";
    }
    m_Wallet._cookieAmount = CookieNumber(inV.at(2));
    m_Wallet._cps = CookieNumber(inV.at(3));
    m_Wallet._totalcookies = CookieNumber(inV.at(4));

    int amountOfItems = std::stoi(inV.at(5));

    return true;
}
