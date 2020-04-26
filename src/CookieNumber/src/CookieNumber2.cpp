//
// Created by remy on 26-04-20.
//

#include <tuple>
#include <utility>
#include "CookieNumber2.h"

bool CookieNumber2::operator==(const CookieNumber2 &rhs) const {
    return std::tie(cookieUnits.at(0), cookieUnits.at(1), cookieUnits.at(2), cookieUnits.at(3), cookieUnits.at(4), cookieUnits.at(5), cookieUnits.at(6), cookieUnits.at(7), cookieUnits.at(8)) ==
           std::tie(rhs.cookieUnits.at(0), rhs.cookieUnits.at(1), rhs.cookieUnits.at(2), rhs.cookieUnits.at(3), rhs.cookieUnits.at(4), rhs.cookieUnits.at(5), rhs.cookieUnits.at(6), rhs.cookieUnits.at(7), rhs.cookieUnits.at(8));
}

bool CookieNumber2::operator!=(const CookieNumber2 &rhs) const {
    return !(rhs == *this);
}

bool CookieNumber2::operator<(const CookieNumber2 &rhs) const {
    return std::tie(cookieUnits.at(0), cookieUnits.at(1), cookieUnits.at(2), cookieUnits.at(3), cookieUnits.at(4), cookieUnits.at(5), cookieUnits.at(6), cookieUnits.at(7), cookieUnits.at(8)) <
           std::tie(rhs.cookieUnits.at(0), rhs.cookieUnits.at(1), rhs.cookieUnits.at(2), rhs.cookieUnits.at(3), rhs.cookieUnits.at(4), rhs.cookieUnits.at(5), rhs.cookieUnits.at(6), rhs.cookieUnits.at(7), rhs.cookieUnits.at(8));
}

bool CookieNumber2::operator>(const CookieNumber2 &rhs) const {
    return rhs < *this;
}

bool CookieNumber2::operator<=(const CookieNumber2 &rhs) const {
    return !(rhs < *this);
}

bool CookieNumber2::operator>=(const CookieNumber2 &rhs) const {
    return !(*this < rhs);
}

std::ostream &operator<<(std::ostream &os, const CookieNumber2 &number) {
    os << "first: " << number.cookieUnits.at(0) << " kilo: " << number.cookieUnits.at(1) << " mega: " << number.cookieUnits.at(2) << " giga: " << number.cookieUnits.at(3)
       << " tera: " << number.cookieUnits.at(4) << " peta: " << number.cookieUnits.at(5) << " exa: " << number.cookieUnits.at(6) << " zetta: " << number.cookieUnits.at(7)
       << " yotta: " << number.cookieUnits.at(8);
    return os;
}

CookieNumber2 operator+(const CookieNumber2 &c1, const CookieNumber2 &c2) {
    CookieNumber2 c;
    size_t cUnits = c.cookieUnits.size();
    for(size_t i = 0; i < cUnits; i++) {
        int unit_sum = c1.cookieUnits.at(i) + c2.cookieUnits.at(i);
        while (unit_sum > 0) {
            if (unit_sum > 999)
            {
                if (c.cookieUnits.at(i) > 999)
                    c.cookieUnits.at(i) -= 999;
                if (i != (cUnits-1))
                    c.cookieUnits.at(i + 1) += 1;
                unit_sum -= 999;
            } else {
                c.cookieUnits.at(i) += unit_sum;
                break;
            }
        }
    }
    return c;
}

CookieNumber2::CookieNumber2(int first, int kilo, int mega, int giga, int tera, int peta, int exa, int zetta,
                             int yotta) {
    cookieUnits.at(0) = first;
    cookieUnits.at(1) = kilo;
    cookieUnits.at(2) = mega;
    cookieUnits.at(3) = giga;
    cookieUnits.at(4) = tera;
    cookieUnits.at(5) = peta;
    cookieUnits.at(6) = exa;
    cookieUnits.at(7) = zetta;
    cookieUnits.at(8) = yotta;
}

int CookieNumber2::getCookieUnits(int unit) {
    if (unit <= cookieUnits.size())
        return cookieUnits.at(unit);
    else
        return 0;
}

CookieNumber2::CookieNumber2() = default;

CookieNumber2::CookieNumber2(const CookieNumber2 &c) = default;//: first(c.first), kilo(c.kilo), mega(c.mega), giga(c.giga), tera(c.tera), peta(c.peta), exa(c.exa), zetta(c.zetta),yotta(c.yotta) {}
