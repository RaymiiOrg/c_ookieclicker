#include "CpsUpgrade.h"

UpgradeCatalog::UpgradeCatalog()
{
    _upgrades.push_back({
        "Cursor", "e",
        {
            {"Sharpened Cursor",    CookieNumber("100"),             CookieNumber("10")},
            {"Gilded Cursor",       CookieNumber("1000"),            CookieNumber("20")},
            {"Arcane Cursor",       CookieNumber("50000"),           CookieNumber("40")},
            {"Cosmic Cursor",       CookieNumber("5000000"),         CookieNumber("60")},
            {"Quantum Cursor",      CookieNumber("200000000"),       CookieNumber("80")},
            {"Transcendent Cursor", CookieNumber("15000000000"),     CookieNumber("90")},
            {"Omnipotent Cursor",   CookieNumber("900000000000"),    CookieNumber("100")},
        }
    });
}

const ItemCpsUpgrades *UpgradeCatalog::getUpgradesForItem(const std::string &itemName) const
{
    for (const auto &u : _upgrades)
        if (u.targetItemName == itemName)
            return &u;
    return nullptr;
}
