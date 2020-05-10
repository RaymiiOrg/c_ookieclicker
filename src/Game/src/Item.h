//
// Created by remy on 20-04-20.
//

#ifndef C_OOKIECLIKER_ITEM_H
#define C_OOKIECLIKER_ITEM_H
#include <string>
#include <vector>
#include "CookieNumber.h"

struct Item {
    std::string name;
    std::string buyOneKey;
    std::string buyMaxKey;

    bool operator<(const Item &rhs) const {
        if (price < rhs.price)
            return true;
        if (rhs.price < price)
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

    CookieNumber price {0};
    CookieNumber cps {0};
    int percentIncreaseWhenBought {0};
};

struct Items {
    Item Cursor {"Cursor", "x", "X", CookieNumber(10), CookieNumber(1), 1};
    Item Grandma {"Grandma", "g", "G", CookieNumber(100), CookieNumber(10), 5};
    Item Farm {"Farm", "f", "F", CookieNumber(1000), CookieNumber(20), 7};
    Item Mine {"Mine", "m", "M", CookieNumber(5000), CookieNumber(50), 10};
    Item Factory {"Factory", "t", "T", CookieNumber(15000), CookieNumber(100), 15};
    Item Bank {"Bank", "b", "B", CookieNumber(50000), CookieNumber(500), 20};
    Item Temple {"Temple", "e", "E", CookieNumber(150000), CookieNumber(1500), 25};
    Item WizardTower {"Wizard Tower", "w", "W", CookieNumber(300000), CookieNumber(2000), 30};
    Item Shipment {"Shipment", "s", "S", CookieNumber(4500000), CookieNumber(2500), 30};

    std::vector<Item> allItems {Cursor, Grandma, Farm, Mine, Factory, Bank, Temple, WizardTower,
                                Shipment};
};



#endif //C_OOKIECLIKER_ITEM_H
