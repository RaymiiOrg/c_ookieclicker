//
// Created by remy on 26-04-20.
//

#ifndef C_OOKIECLIKER_COOKIENUMBER_H
#define C_OOKIECLIKER_COOKIENUMBER_H


#include <ostream>
#include <vector>
#include <map>

class CookieNumber {
public:
    CookieNumber(int first, int kilo, int mega, int giga, int tera, int peta, int exa, int zetta, int yotta);
    CookieNumber();
    CookieNumber(int first, int kilo);
    CookieNumber(const CookieNumber &c);
    friend std::ostream &operator<<(std::ostream &os, const CookieNumber &number);
    bool operator==(const CookieNumber &rhs) const;
    bool operator!=(const CookieNumber &rhs) const;
    bool operator<(const CookieNumber &rhs) const;
    bool operator>(const CookieNumber &rhs) const;
    bool operator<=(const CookieNumber &rhs) const;
    bool operator>=(const CookieNumber &rhs) const;
    friend CookieNumber operator+(const CookieNumber &c1, const CookieNumber &c2);
    
private:
    int u0_first{};
    int u1_kilo{};
    int u2_mega{};
    int u3_giga{};
    int u4_tera{};
    int u5_peta{};
    int u6_exa{};
    int u7_zetta{};
    int u8_yotta{};
    static constexpr int amount_of_units = 8;
};


#endif //C_OOKIECLIKER_COOKIENUMBER_H
