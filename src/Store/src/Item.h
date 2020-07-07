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
    Item Farm {"Farm", "f", "F", CookieNumber(1000), CookieNumber(20)};
    Item Mine {"Mine", "m", "M", CookieNumber(5000), CookieNumber(50)};
    Item Factory {"Factory", "t", "T", CookieNumber(15000), CookieNumber(100)};
    Item Bank {"Bank", "b", "B", CookieNumber(50000), CookieNumber(500)};
    Item Temple {"Temple", "e", "E", CookieNumber(150000), CookieNumber(1500)};
    Item WizardTower {"Wizard Tower", "w", "W", CookieNumber(300000), CookieNumber(2000)};
    Item Shipment {"Shipment", "o", "O", CookieNumber(4500000), CookieNumber(2500)};
    Item Alchemylab {"Alchemy Lab", "a", "A", CookieNumber("900000000"), CookieNumber(3500)};
    Item Portal {"Portal", "p", "P", CookieNumber("4500000000"), CookieNumber(5000)};
//    Item Timemachine {"Time Machine", "i", "I", CookieNumber(), CookieNumber(), };
//    Item Antimattercondenser {"Antimatter Condenser", "y", "Y", CookieNumber(), CookieNumber(), };
//    Item Prism {"Prism", "Y", "Y", CookieNumber(), CookieNumber(), };
//    Item Chancemaker {"Chance maker", "z", "Z", CookieNumber(), CookieNumber(), };
//    Item FractalEngine {"Fractal Engine", "H", "H", CookieNumber(), CookieNumber(), };
//    Item JavascriptConsole {"Javascript Console", "j", "J", CookieNumber(), CookieNumber(), };

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
    };

public:
    std::vector<Item> getAllItems() { return allItems; };
};





#endif //C_OOKIECLIKER_ITEM_H
