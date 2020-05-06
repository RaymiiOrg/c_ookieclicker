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
 * Example: 0: 382, 1: 222, 2: 9 will return the string
 * 9222382.
 */
std::ostream &operator<<(std::ostream &os, const CookieNumber2 &number) {
    bool nonZeroNumberPrinted = false;
    for (auto it = number.cookieUnits.rbegin(); it != number.cookieUnits.rend(); ++it ) {
        if (*it != 0 and !nonZeroNumberPrinted) {
            os << *it;
            nonZeroNumberPrinted = true;
            continue;
        }
        /** If we have a number like 0: 0, 1: 0, 2: 0, 3: 1
         * then without this check it would print just 1. **/
        if (nonZeroNumberPrinted)
            os << *it;
    }
//    os << "\n\n";
//    for (auto it = number.cookieUnits.begin(); it != number.cookieUnits.end(); ++it ) {
//        auto i = std::distance(number.cookieUnits.begin(), it);
//        os << "ASSERT_EQ(c5.getCookieUnits("<<i << ")," << *it << "); \n";
//    }
//    os << "\n\n";
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
        auto remainder = *it % limitPerUnit;
        auto fitsInTimes = (*it - remainder) / limitPerUnit;
        if (fitsInTimes > 0) {
            if (std::next(it) == cookieUnits.end()) {
                cookieUnits.push_back(0); // iterator pointers are now invalid
                // make sure iterator pointers are valid again:
                it = std::next(cookieUnits.begin(), cookieUnits.size() - 2);
            }
            *std::next(it) += fitsInTimes;
            *it = remainder;
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

CookieNumber2 operator*(const CookieNumber2 &lhs, int rhs) {
    CookieNumber2 c(lhs);
    for(int i = 1; i < rhs; ++i)
    {
        c = c + CookieNumber2(lhs);
    }
    return c;
}

CookieNumber2 operator*(const CookieNumber2 &lhs, const CookieNumber2 &rhs) {
    CookieNumber2 c(lhs);
    if (c.cookieUnits.size() < rhs.cookieUnits.size())
        c.cookieUnits.resize(rhs.cookieUnits.size());

    for(auto it = lhs.cookieUnits.begin(); it != lhs.cookieUnits.end(); ++it)
    {
        auto i = std::distance(lhs.cookieUnits.begin(), it);
        if (rhs.cookieUnits.size() > i)
            c.cookieUnits.at(i) = lhs.cookieUnits.at(i) * rhs.cookieUnits.at(i);
        else
            c.cookieUnits.at(i) = lhs.cookieUnits.at(i);
    }
    c.redistributeUnitsUp();
    return c;
}

CookieNumber2 operator*(int lhs, const CookieNumber2 &rhs) {
    return CookieNumber2();
}

CookieNumber2::CookieNumber2(const CookieNumber2 &c) = default;