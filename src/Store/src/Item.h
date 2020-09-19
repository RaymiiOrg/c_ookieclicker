//
// Created by remy on 20-04-20.
//

#ifndef C_OOKIECLIKER_ITEM_H
#define C_OOKIECLIKER_ITEM_H

#include "CookieNumbers.h"
#include <string>
#include <vector>

struct Item {
    std::string name;
    std::string buyKey;
    CookieNumber baseCost{1};
    CookieNumber cps{1};

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
                "a",
                CookieNumber(15),
                CookieNumber(".1")
    };
    Item Grandma{"Grandma",
                 "b",
                 CookieNumber(100),
                 CookieNumber(1)
    };
    Item Farm{"Farm",
              "d",
              CookieNumber(1100),
              CookieNumber(8)
    };
    Item Mine{"Mine",
              "e",
              CookieNumber(12000),
              CookieNumber(47)
    };
    Item Factory{"Factory",
                 "f",
                 CookieNumber(130000),
                 CookieNumber(260)
    };
    Item Bank{"Bank",
              "g",
              CookieNumber(1400000),
              CookieNumber(1400)
    };
    Item Temple{"Temple",
                "h",
                CookieNumber(20000000),
                CookieNumber(7800)
    };
    Item WizardTower{"Wizard Tower",
                     "i",
                     CookieNumber(330000000),
                     CookieNumber(44000)
    };
    Item Shipment{"Shipment",
                  "j",
                  CookieNumber(5100000000),
                  CookieNumber(260000)
    };
    Item Alchemylab{"Alchemy Lab",
                    "k",
                    CookieNumber("75000000000"),
                    CookieNumber(1600000)
    };
    Item Portal{"Portal",
                "l",
                CookieNumber("1000000000000"),
                CookieNumber(10000000)
    };
    Item Timemachine{
            "Time Machine",
            "m",
            CookieNumber("14000000000000"),
            CookieNumber(65000000),
    };
    Item Antimattercondenser{
            "Antimatter Condenser",
            "n",
            CookieNumber("170000000000000"),
            CookieNumber(430000000),
    };
    Item Prism{
            "Prism",
            "o",
            CookieNumber("2100000000000000"),
            CookieNumber("2900000000"),
    };
    Item Chancemaker{
            "Chance maker",
            "p",
            CookieNumber("26000000000000000"),
            CookieNumber("21000000000"),
    };
    Item FractalEngine{
            "Fractal Engine",
            "q",
            CookieNumber("310000000000000000"),
            CookieNumber("150000000000"),
    };
    Item JavascriptConsole{
            "Javascript Console",
            "r",
            CookieNumber("71000000000000000000"),
            CookieNumber("1100000000000"),
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
    };

public:
    std::vector<Item> getAllItems() { return allItems; };
};

#endif //C_OOKIECLIKER_ITEM_H
