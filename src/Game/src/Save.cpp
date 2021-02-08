#include "Save.h"

Save::Save(std::string filename, Inventory *Inventory, Wallet *wallet, Store *store, int format) :
        saveFileName(std::move(
        filename)),
        inventory(Inventory), wallet(wallet), store(store), format(format) {}

bool Save::save()
{
    if (!inventory || !wallet || !format)
        return false;

    switch (format) {
        case 1:     return saveFormatOne();
        case 2:     return saveFormatTwo();
        default:    return false;
    }
}

bool Save::load()
{
    if (!inventory || !wallet || !format)
        return false;

    switch (getFormat()) {
        case 1:     return loadFormatOne();
        case 2:     return loadFormatTwo();
        default:    return false;
    }
}

void Save::resetGameData() {
    wallet->reset();
    inventory->reset();
    store->reset();
}

bool Save::saveFormatOne()
{
    std::ofstream out(saveFileName);
    if (out.fail())
        return false;

    save_step_1_Header(out);
    format = 1;
    save_step_2_Format(out);
    save_step_3_CookieAmount(out);
    save_step_4_CPS(out);
    save_step_5_TotalCookies(out);
    save_step_6_Items(out);

    return true;
}

bool Save::loadFormatOne()
{
    auto inV = getSaveData();
    if (inV.empty())
        return false;

    resetGameData();

    load_step_3_CookieAmount(inV);
    load_step_4_CPS(inV);
    load_step_5_TotalCookies(inV);
    load_step_6_Items(inV);

    return true;
}

bool Save::loadFormatTwo() {
    auto inV = getSaveData();
    if (inV.empty())
        return false;

    resetGameData();

    load_step_3_CookieAmount(inV);
    load_step_4_CPS(inV);
    load_step_5_TotalCookies(inV);
    load_step_6_Items(inV);
    load_step_7_CookiesViaInput(inV);
    load_step_8_CookiesPerTap(inV);
    return true;
}

bool Save::saveFormatTwo() {
    std::ofstream out(saveFileName);
    if (out.fail())
        return false;

    save_step_1_Header(out);
    format = 2;
    save_step_2_Format(out);
    save_step_3_CookieAmount(out);
    save_step_4_CPS(out);
    save_step_5_TotalCookies(out);
    save_step_6_Items(out);
    save_step_7_CookiesViaInput(out);
    save_step_8_CookiesPerTap(out);
    return true;
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

void Save::save_step_1_Header(std::ofstream &out) {
    out << "# c_ookieClicker savegame, by https://raymii.org"
        << ";";
}

void Save::save_step_2_Format(std::ofstream &out) const {
    out << std::to_string(format) << ";";
}

void Save::save_step_3_CookieAmount(std::ofstream &out) const {
    out << wallet->getCookieAmount().str(0, std::ios_base::fixed) << ";";
}

void Save::save_step_4_CPS(std::ofstream &out) const {
    out << wallet->getCps().str(0, std::ios_base::fixed) << ";";
}

void Save::save_step_5_TotalCookies(std::ofstream &out) {
    out << wallet->getTotalcookies().str(0, std::ios_base::fixed) << ";";
}

void Save::save_step_6_Items(std::ofstream &out) const {
    out << inventory->getInventory().size() << ";";
    for (const auto &item : inventory->getInventory())
    {
        out << item.first << "," << item.second.str(0, std::ios_base::fixed) << ";";
    }
}

void Save::save_step_7_CookiesViaInput(std::ofstream &out) {
    out << wallet->getCookiesViaInput().str(0, std::ios_base::fixed) << ";";
}

void Save::save_step_8_CookiesPerTap(std::ofstream &out) {
    out << inventory->getCookiesPerTap().str(0, std::ios_base::fixed) << ";";
}


void Save::load_step_3_CookieAmount(std::vector<std::string> &inV) { wallet->setCookieAmount(CookieNumber(inV.at(2))); }

void Save::load_step_4_CPS(std::vector<std::string> &inV) { wallet->setCps(CookieNumber(inV.at(3))); }

void Save::load_step_5_TotalCookies(std::vector<std::string> &inV) { wallet->setTotalcookies(CookieNumber(inV.at(4))); }

void Save::load_step_6_Items(std::vector<std::string> &inV) {
    int amountOfItems = loadAmountOfItems(inV);
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
            inventory->addItem(itemName, itemAmount);
        }
    }
}

int Save::loadAmountOfItems(std::vector<std::string> &inV) {
    if (inV.size() >= 5)
    {
        return std::stoi(inV.at(5));
    }
    else
    {
        return -1;
    }
}

void Save::load_step_7_CookiesViaInput(std::vector<std::string> &inV) {
    int positionInSave = loadAmountOfItems(inV) + 1;
    wallet->incrementCookieViaInput(CookieNumber(positionInSave));
}

void Save::load_step_8_CookiesPerTap(std::vector<std::string> &inV) {
    int positionInSave = loadAmountOfItems(inV) + 2;
    inventory->incrementCookiesPerTap(CookieNumber(positionInSave));
}

