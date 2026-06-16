#ifndef C_OOKIECLIKER_ITEM_H
#define C_OOKIECLIKER_ITEM_H

#include "CookieNumbers.h"
#include <string>
#include <vector>

struct ItemTier {
    std::string name;
    CookieNumber cost;
    CookieNumber bonus;
};

struct Item {
    std::string name;
    std::string buyKey;
    CookieNumber baseCost{1};
    CookieNumber cps{0};
    CookieNumber cookiesPerTap{0};
    std::vector<ItemTier> tiers{};

    /** The index of the tier that becomes active when you own `count` of
     * this item, or -1 if the item is not tiered or `count` is beyond the
     * defined tiers. Single source of truth for tier lookups. */
    int tierIndexFor(const CookieNumber &count) const {
        for (size_t i = 0; i < tiers.size(); ++i)
            if (count == CookieNumber(i)) return static_cast<int>(i);
        return -1;
    }

    std::string getDisplayName(const CookieNumber &count) const {
        int i = tierIndexFor(count);
        return i >= 0 ? tiers[i].name : name;
    }

    CookieNumber getTierBonus(const CookieNumber &count) const {
        int i = tierIndexFor(count);
        return i >= 0 ? tiers[i].bonus : cookiesPerTap;
    }

    /** CPS gained from owning `amount` of this item under the given CPS
     * multiplier. Single source of truth shared by the buy command and the
     * store preview so the displayed gain always matches what is granted. */
    CookieNumber cpsGain(const CookieNumber &amount, const CookieNumber &multiplier) const {
        return cps * amount * multiplier;
    }

    bool operator<(const Item &rhs) const {
        if (baseCost < rhs.baseCost)
            return true;
        if (rhs.baseCost < baseCost)
            return false;
        return cps < rhs.cps;
    }

    bool operator>(const Item &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Item &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Item &rhs) const {
        return !(*this < rhs);
    }
};

class Items {
private:
    Item Cursor{"Cursor",
                "e",
                CookieNumber(15),
                CookieNumber(".1")
    };
    Item Grandma{"Grandma",
                 "f",
                 CookieNumber(100),
                 CookieNumber(1)
    };
    Item Farm{"Farm",
              "g",
              CookieNumber(1100),
              CookieNumber(8)
    };
    Item Mine{"Mine",
              "h",
              CookieNumber(12000),
              CookieNumber(47)
    };
    Item Factory{"Factory",
                 "i",
                 CookieNumber(130000),
                 CookieNumber(260)
    };
    Item Bank{"Bank",
              "j",
              CookieNumber(1400000),
              CookieNumber(1400)
    };
    Item Temple{"Temple",
                "k",
                CookieNumber(20000000),
                CookieNumber(7800)
    };
    Item WizardTower{"Wizard Tower",
                     "l",
                     CookieNumber(330000000),
                     CookieNumber(44000)
    };
    Item Shipment{"Shipment",
                  "m",
                  CookieNumber(5100000000),
                  CookieNumber(260000)
    };
    Item Alchemylab{"Alchemy Lab",
                    "n",
                    CookieNumber("75000000000"),
                    CookieNumber(1600000)
    };
    Item Portal{"Portal",
                "o",
                CookieNumber("1000000000000"),
                CookieNumber(10000000)
    };
    Item Timemachine{
            "Time Machine",
            "p",
            CookieNumber("14000000000000"),
            CookieNumber(65000000),
    };
    Item Antimattercondenser{
            "Antimatter Condenser",
            "r",
            CookieNumber("170000000000000"),
            CookieNumber(430000000),
    };
    Item Prism{
            "Prism",
            "s",
            CookieNumber("2100000000000000"),
            CookieNumber("2900000000"),
    };
    Item Chancemaker{
            "Chance maker",
            "t",
            CookieNumber("26000000000000000"),
            CookieNumber("21000000000"),
    };
    Item FractalEngine{
            "Fractal Engine",
            "u",
            CookieNumber("310000000000000000"),
            CookieNumber("150000000000"),
    };
    Item JavascriptConsole{
            "Javascript Console",
            "v",
            CookieNumber("71000000000000000000"),
            CookieNumber("1100000000000"),
    };

    Item CookieTap{
            "Cookie Tap",
            "w",
            CookieNumber(0),
            CookieNumber(0),
            CookieNumber(0),
            {
                {"Cookie Upgrade",                CookieNumber(100),        CookieNumber(1)},
                {"Pro Cookie Upgrade",            CookieNumber(1000),       CookieNumber(2)},
                {"Pro Max Cookie Upgrade",        CookieNumber(15000),      CookieNumber(10)},
                {"Cookie Monster Cookie Upgrade", CookieNumber(500000),     CookieNumber(100)},
                {"Galactic Cookie Upgrade",       CookieNumber(25000000),   CookieNumber(1000)},
            }
    };

    std::vector<Item> allItems{
            Cursor,
            Grandma,
            Farm,
            Mine,
            Factory,
            Bank,
            Temple,
            WizardTower,
            Shipment,
            Alchemylab,
            Portal,
            Timemachine,
            Antimattercondenser,
            Prism,
            Chancemaker,
            FractalEngine,
            JavascriptConsole,
            CookieTap,
    };

public:
    std::vector<Item> getAllItems() { return allItems; };
};

#endif //C_OOKIECLIKER_ITEM_H
