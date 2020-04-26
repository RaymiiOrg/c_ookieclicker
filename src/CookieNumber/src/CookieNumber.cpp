//
// Created by remy on 26-04-20.
//

#include <tuple>
#include "CookieNumber.h"

bool CookieNumber::operator==(const CookieNumber &rhs) const {
    return std::tie(u0_first, u1_kilo, u2_mega, u3_giga, u4_tera, u5_peta, u6_exa, u7_zetta, u8_yotta) ==
           std::tie(rhs.u0_first, rhs.u1_kilo, rhs.u2_mega, rhs.u3_giga, rhs.u4_tera, rhs.u5_peta, rhs.u6_exa, rhs.u7_zetta, rhs.u8_yotta);
}

bool CookieNumber::operator!=(const CookieNumber &rhs) const {
    return !(rhs == *this);
}

bool CookieNumber::operator<(const CookieNumber &rhs) const {
    return std::tie(u0_first, u1_kilo, u2_mega, u3_giga, u4_tera, u5_peta, u6_exa, u7_zetta, u8_yotta) <
           std::tie(rhs.u0_first, rhs.u1_kilo, rhs.u2_mega, rhs.u3_giga, rhs.u4_tera, rhs.u5_peta, rhs.u6_exa, rhs.u7_zetta, rhs.u8_yotta);
}

bool CookieNumber::operator>(const CookieNumber &rhs) const {
    return rhs < *this;
}

bool CookieNumber::operator<=(const CookieNumber &rhs) const {
    return !(rhs < *this);
}

bool CookieNumber::operator>=(const CookieNumber &rhs) const {
    return !(*this < rhs);
}

std::ostream &operator<<(std::ostream &os, const CookieNumber &number) {
    os << "first: " << number.u0_first << " kilo: " << number.u1_kilo << " mega: " << number.u2_mega << " giga: " << number.u3_giga
       << " tera: " << number.u4_tera << " peta: " << number.u5_peta << " exa: " << number.u6_exa << " zetta: " << number.u7_zetta
       << " yotta: " << number.u8_yotta;
    return os;
}

CookieNumber operator+(const CookieNumber &c1, const CookieNumber &c2) {
    CookieNumber c(c1);
    int u0_plus = c.u0_first + c2.u0_first;
    while (u0_plus >= 0) {
        if (u0_plus > 999)
        {
            c.u0_first -= 999;
            c.u1_kilo += 1;
            u0_plus -= 999;
        } else {
            c.u0_first = u0_plus;
            break;
        }
    }
    int u1_plus = c.u1_kilo + c2.u1_kilo;
    while (u1_plus >= 0) {
        if (u1_plus > 999)
        {
            c.u1_kilo -= 999;
            c.u2_mega += 1;
            u1_plus -= 999;
        } else {
            c.u1_kilo = u1_plus;
            break;
        }
    }
    return c;
}

CookieNumber::CookieNumber(int first, int kilo, int mega, int giga, int tera, int peta, int exa, int zetta, int yotta)
        : u0_first(first), u1_kilo(kilo), u2_mega(mega), u3_giga(giga), u4_tera(tera), u5_peta(peta), u6_exa(exa), u7_zetta(zetta),
          u8_yotta(yotta) {}

CookieNumber::CookieNumber() = default;

CookieNumber::CookieNumber(const CookieNumber &c) = default;//: first(c.first), kilo(c.kilo), mega(c.mega), giga(c.giga), tera(c.tera), peta(c.peta), exa(c.exa), zetta(c.zetta),yotta(c.yotta) {}

CookieNumber::CookieNumber(int first, int kilo)
        : u0_first(first), u1_kilo(kilo) {}