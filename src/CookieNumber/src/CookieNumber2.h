//
// Created by remy on 26-04-20.
//

#ifndef C_OOKIECLIKER_CookieNumber2_H
#define C_OOKIECLIKER_CookieNumber2_H


#include <ostream>
#include <vector>
#include <map>
#include <iostream>

class CookieNumber2 {
public:
    explicit CookieNumber2(int first = 0, int kilo = 0, int mega = 0, int giga = 0, int tera = 0, int peta = 0,
            int exa = 0, int zetta = 0, int yotta = 0);
    CookieNumber2(const CookieNumber2 &c);
    friend std::ostream &operator<<(std::ostream &os, const CookieNumber2 &number);
    bool operator==(const CookieNumber2 &rhs) const;
    bool operator!=(const CookieNumber2 &rhs) const;
    bool operator<(const CookieNumber2 &rhs) const;
    bool operator>(const CookieNumber2 &rhs) const;
    bool operator<=(const CookieNumber2 &rhs) const;
    bool operator>=(const CookieNumber2 &rhs) const;
    friend CookieNumber2 operator+(const CookieNumber2 &lhs, const CookieNumber2 &rhs);
    friend CookieNumber2 operator+(const CookieNumber2 &lhs, int rhs);
    friend CookieNumber2 operator+(int lhs, const CookieNumber2 &rhs);
    int getCookieUnits(int unit);
    int getAmountOfUnits();

protected:
    std::vector<long long int> cookieUnits {0,0,0,0,0,0,0,0,0};
    int limitPerUnit = 1000;
//  const int limitPerUnit = 1000;
    bool redistributeUnitsUp();


};


#endif //C_OOKIECLIKER_CookieNumber2_H
