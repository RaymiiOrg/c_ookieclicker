//
// Created by remy on 20-04-20.
//

#ifndef C_OOKIECLIKER_ITEM_H
#define C_OOKIECLIKER_ITEM_H
#include <string>
#include <vector>
#include "CookieNumbers.h"

struct Item {
    std::string name;
    std::string buyOneKey;
    std::string buyMaxKey;

    bool operator<(const Item &rhs) const {
        if (baseCost < rhs.baseCost)
            return true;
        if (rhs.baseCost < baseCost)
            return false;
        return cps < rhs.cps;
    }

    bool operator>(const Item &rhs) {
        return rhs < *this;
    }

    bool operator<=(const Item &rhs) {
        return !(rhs < *this);
    }

    bool operator>=(const Item &rhs) const {
        return !(*this < rhs);
    }

    CookieNumber baseCost {1};
    CookieNumber cps {1};
};

class Items {
private:
    Item Key {"Key", "k", "K", CookieNumber(15), CookieNumber(1)};
    Item Grandma {"Grandma", "g", "G", CookieNumber(100), CookieNumber(10)};
    Item Farm {"Farm", "f", "F", CookieNumber(1100), CookieNumber(20)};
    Item Mine {"Mine", "m", "M", CookieNumber(12000), CookieNumber(50)};
    Item Factory {"Factory", "t", "T", CookieNumber(130000), CookieNumber(260)};
    Item Bank {"Bank", "b", "B", CookieNumber(1400000), CookieNumber(1400)};
    Item Temple {"Temple", "e", "E", CookieNumber(20000000), CookieNumber(7800)};
    Item WizardTower {"Wizard Tower", "w", "W", CookieNumber(330000000), CookieNumber(44000)};
    Item Shipment {"Shipment", "o", "O", CookieNumber(5100000000), CookieNumber(260000)};
    Item Alchemylab {"Alchemy Lab", "a", "A", CookieNumber("75000000000"), CookieNumber(1600000)};
    Item Portal {"Portal", "p", "P", CookieNumber("1000000000000"), CookieNumber(10000000)};
    Item Timemachine {"Time Machine", "i", "I", CookieNumber("14000000000000"), CookieNumber(65000000), };
    Item Antimattercondenser {"Antimatter Condenser", "y", "Y", CookieNumber("170000000000000"), CookieNumber(430000000), };
    Item Prism {"Prism", "Y", "Y", CookieNumber("2100000000000000"), CookieNumber("2900000000"), };
    Item Chancemaker {"Chance maker", "z", "Z", CookieNumber("26000000000000000"), CookieNumber("21000000000"), };
    Item FractalEngine {"Fractal Engine", "h", "H", CookieNumber("310000000000000000"), CookieNumber("150000000000"), };
    Item JavascriptConsole {"Javascript Console", "j", "J", CookieNumber("71000000000000000000"), CookieNumber("1100000000000"), };

    std::vector<Item> allItems {
        Key,
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
