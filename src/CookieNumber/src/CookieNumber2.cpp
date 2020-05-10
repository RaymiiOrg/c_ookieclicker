//
// Created by remy on 26-04-20.
//

#include "CookieNumber2.h"

/* Constructor */
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

/* Comparison */

bool CookieNumber2::operator==(const CookieNumber2 &rhs) const {
    return cookieUnits == rhs.cookieUnits;
}

bool CookieNumber2::operator!=(const CookieNumber2 &rhs) const {
    return !(rhs == *this);
}

bool CookieNumber2::operator<(const CookieNumber2 &rhs) const {
    if (cookieUnits.size() > rhs.cookieUnits.size())
        return false;
    bool seenLt = false;
    for (auto it = cookieUnits.rbegin(); it != cookieUnits.rend(); ++it)
    {
        auto reverse_i = (cookieUnits.size() - 1) - (it - cookieUnits.rbegin());
        auto i = std::distance(cookieUnits.rbegin(), it);
        auto left = *it;
        auto right = rhs.cookieUnits.at(reverse_i);
        if (left == right)
            continue;

        if (left > right)
        {
            if (!seenLt)
                return seenLt;
        } else {

                seenLt = true;
        }
    }
    return seenLt;
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

/* Output */

/**
 * return the number in a human-readable format. (last element
 * as the first number, since it's probably the highest unit).
 * Example: 0: 382, 1: 222, 2: 9 will return the string
 * 9222382.
 */
std::ostream &operator<<(std::ostream &os, const CookieNumber2 &number) {
    bool nonZeroNumberPrinted = false;
    for (auto it = number.cookieUnits.rbegin(); it != number.cookieUnits.rend(); ++it) {
        if (*it != 0 and !nonZeroNumberPrinted) {
            os << *it;
            nonZeroNumberPrinted = true;
            continue;
        }
        /** If we have a number like 0: 0, 1: 0, 2: 0, 3: 1
         * then without this check it would print just 1. **/
        if (nonZeroNumberPrinted)
            os << std::setw(3) << std::setfill('0') << *it;
    }
    return os;
}


/* Addition */

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

CookieNumber2 operator+(const CookieNumber2 &lhs, int rhs) {
    CookieNumber2 r(rhs);
    return lhs + r;
}

CookieNumber2 operator+(int lhs, const CookieNumber2 &rhs) {
    CookieNumber2 l(lhs);
    return l + rhs;
}

/* Multiplication */

CookieNumber2 operator*(const CookieNumber2 &lhs, int rhs) {
    CookieNumber2 c(lhs);
    for(int i = 1; i < rhs; ++i)
    {
        c = c + CookieNumber2(lhs);
    }
    return c;
}

CookieNumber2 operator*(int lhs, const CookieNumber2 &rhs) {
    CookieNumber2 c(rhs);
    for(int i = 1; i < lhs; ++i)
    {
        c = c + CookieNumber2(rhs);
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

/* Substraction */
CookieNumber2 operator-(const CookieNumber2 &lhs, const CookieNumber2 &rhs) {
    CookieNumber2 c(lhs);
    if (c.cookieUnits.size() < rhs.cookieUnits.size())
        c.cookieUnits.resize(rhs.cookieUnits.size());

    for (auto it = c.cookieUnits.begin(); it != c.cookieUnits.end(); ++it) {
        auto i = std::distance(c.cookieUnits.begin(), it);
        auto left = c.cookieUnits.at(i);
        auto right = rhs.cookieUnits.at(i);
        if ((left == 0 and right == 0) or (right == 0))
            continue;

        auto minus = left - right;
        if (minus < 0) {
            if (std::next(it) != c.cookieUnits.end()) {
                if (*std::next(it) > 0) {
                    *std::next(it) -= 1;
                    *it += c.limitPerUnit;
                } else {
                    c = CookieNumber2(-1);
                    return c;
                }
            } else {
                c = CookieNumber2(-1);
                return c;
            }
        }
        *it -= std::abs(minus);
    }

    return c;
}


CookieNumber2 operator-(const CookieNumber2 &lhs, int rhs) {
    return lhs - CookieNumber2(rhs);
}

/* Helpers */
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

int CookieNumber2::getCookieUnits(int unit) {
    if (unit <= cookieUnits.size())
        return static_cast<int>(cookieUnits.at(unit));
    else
        return 0;
}

int CookieNumber2::getAmountOfUnits() {
    return cookieUnits.size();
}

std::string CookieNumber2::printArray() {
    std::string result;
    for (auto it = cookieUnits.begin(); it != cookieUnits.end(); ++it) {
        auto i = std::distance(cookieUnits.begin(), it);
        result += std::to_string(i) + "=" + std::to_string(*it) + "; ";
    }
    return result;
}

CookieNumber2 operator-(int lhs, const CookieNumber2 &rhs) {
    return CookieNumber2();
}

