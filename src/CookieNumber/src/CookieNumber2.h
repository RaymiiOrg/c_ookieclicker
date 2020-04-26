//
// Created by remy on 26-04-20.
//

#ifndef C_OOKIECLIKER_CookieNumber2_H
#define C_OOKIECLIKER_CookieNumber2_H


#include <ostream>
#include <vector>
#include <map>

class CookieNumber2 {
public:
    CookieNumber2();
    explicit CookieNumber2(int first, int kilo = 0, int mega = 0, int giga = 0, int tera = 0, int peta = 0,
            int exa = 0, int zetta = 0, int yotta = 0);
    CookieNumber2(const CookieNumber2 &c);
    friend std::ostream &operator<<(std::ostream &os, const CookieNumber2 &number);
    bool operator==(const CookieNumber2 &rhs) const;
    bool operator!=(const CookieNumber2 &rhs) const;
    bool operator<(const CookieNumber2 &rhs) const;
    bool operator>(const CookieNumber2 &rhs) const;
    bool operator<=(const CookieNumber2 &rhs) const;
    bool operator>=(const CookieNumber2 &rhs) const;
    friend CookieNumber2 operator+(const CookieNumber2 &c1, const CookieNumber2 &c2);

protected:
    std::map<int,int> cookieUnits {
            {0,0},
            {1,0},
            {2,0},
            {3,0},
            {4,0},
            {5,0},
            {6,0},
            {7,0},
            {8,0},
            {9,0}
    };
public:
    int getCookieUnits(int unit);

};


#endif //C_OOKIECLIKER_CookieNumber2_H
