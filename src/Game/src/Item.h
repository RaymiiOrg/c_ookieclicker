//
// Created by remy on 20-04-20.
//

#ifndef C_OOKIECLIKER_ITEM_H
#define C_OOKIECLIKER_ITEM_H
#include <string>
#include <vector>

struct Item {
    std::string name;
    std::string buyOneKey;
    std::string buyAllKey;

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

    double price {0};
    double cps {0};
    int percentIncreaseWhenBought {0};
};

struct Items {
    Item Cursor {"Cursor", "c", "C", 10, 0.1, 1};
    Item Grandma {"Grandma", "g", "G", 100, 1, 5};

    std::vector<Item> allItems {Cursor, Grandma};
};



#endif //C_OOKIECLIKER_ITEM_H
