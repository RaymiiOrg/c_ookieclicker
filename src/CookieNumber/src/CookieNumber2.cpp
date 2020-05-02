//
// Created by remy on 26-04-20.
//


#include "CookieNumber2.h"

bool CookieNumber2::operator==(const CookieNumber2 &rhs) const {
    return cookieUnits == rhs.cookieUnits;
}

bool CookieNumber2::operator!=(const CookieNumber2 &rhs) const {
    return !(rhs == *this);
}

bool CookieNumber2::operator<(const CookieNumber2 &rhs) const {
    return cookieUnits < rhs.cookieUnits;
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

/**
 * return the number in a human-readable format. (last element
 * as the first number, since it's probably the highest unit).
 */
std::ostream &operator<<(std::ostream &os, const CookieNumber2 &number) {
    for (auto it = number.cookieUnits.rbegin(); it != number.cookieUnits.rend(); ++it ) {
        if (*it != 0)
            os << *it;
    }

    return os;
}

CookieNumber2 operator+(const CookieNumber2 &lhs, const CookieNumber2 &rhs) {
    CookieNumber2 c(lhs);
    if (c.cookieUnits.size() < rhs.cookieUnits.size())
        c.cookieUnits.resize(rhs.cookieUnits.size()+1);
    for(size_t i = 0; i < c.cookieUnits.size(); ++i) {
        c.cookieUnits.at(i) += rhs.cookieUnits.at(i);
    }
    c.redistributeUnitsUp();
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
    redistributeUnitsUp();
}

int CookieNumber2::getCookieUnits(int unit) {
    if (unit <= cookieUnits.size())
        return static_cast<int>(cookieUnits.at(unit));
    else
        return 0;
}

bool CookieNumber2::redistributeUnitsUp() {
    for (auto it = cookieUnits.begin(); it != cookieUnits.end(); ++it) {
        auto rest = *it % limitPerUnit;
        auto fitsInTimes = (*it - rest) / limitPerUnit;
        if (fitsInTimes > 0) {
            if (std::next(it) == cookieUnits.end()) {
                cookieUnits.push_back(0); // iterator pointers are now invalid
                // make sure iterator pointers are valid again:
                it = std::next(cookieUnits.begin(), cookieUnits.size() - 2);
            }
            *std::next(it) += fitsInTimes;
            *it = rest;
        }
    }
    return true;
}

int CookieNumber2::getAmountOfUnits() {
    return cookieUnits.size();
}

CookieNumber2 operator+(const CookieNumber2 &lhs, int rhs) {
    CookieNumber2 r(rhs);
    return lhs + r;
}

CookieNumber2 operator+(int lhs, const CookieNumber2 &rhs) {
    CookieNumber2 l(lhs);
    return l + rhs;
}

CookieNumber2::CookieNumber2(const CookieNumber2 &c) = default;