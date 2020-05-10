//
// Created by remy on 26-04-20.
//

#include "CookieNumber.h"

/* Constructor */
CookieNumber::CookieNumber(int first, int kilo, int mega, int giga, int tera, int peta, int exa, int zetta,
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

bool CookieNumber::operator==(const CookieNumber &rhs) const {
    return cookieUnits == rhs.cookieUnits;
}

bool CookieNumber::operator!=(const CookieNumber &rhs) const {
    return !(rhs == *this);
}

bool CookieNumber::operator<(const CookieNumber &rhs) const {
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

bool CookieNumber::operator>(const CookieNumber &rhs) const {
    return rhs < *this;
}

bool CookieNumber::operator<=(const CookieNumber &rhs) const {
    return !(rhs < *this);
}

bool CookieNumber::operator>=(const CookieNumber &rhs) const {
    return !(*this < rhs);
}

/* Output */

/**
 * return the number in a human-readable format. (last element
 * as the first number, since it's probably the highest unit).
 * Example: 0: 382, 1: 222, 2: 9 will return the string
 * 9222382.
 */
std::ostream &operator<<(std::ostream &os, const CookieNumber &number) {
    bool nonZeroNumberPrinted = false;
    bool printedAnything = false;
    for (auto it = number.cookieUnits.rbegin(); it != number.cookieUnits.rend(); ++it) {
        if (*it != 0 and !nonZeroNumberPrinted) {
            os << *it;
            nonZeroNumberPrinted = true;
            printedAnything = true;
            continue;
        }
        /** If we have a number like 0: 0, 1: 0, 2: 0, 3: 1
         * then without this check it would print just 1. **/
        if (nonZeroNumberPrinted) {
            os << std::setw(3) << std::setfill('0') << *it;
            printedAnything = true;
        }
    }
    if (!printedAnything)
        os << "0";

    return os;
}

std::string CookieNumber::str() const {
    std::stringstream output;
    output << *this;
    return output.str();
}


/* Addition */

CookieNumber operator+(const CookieNumber &lhs, const CookieNumber &rhs) {
    CookieNumber c(lhs);
    if (c.cookieUnits.size() < rhs.cookieUnits.size())
        c.cookieUnits.resize(rhs.cookieUnits.size());
    for(size_t i = 0; i < c.cookieUnits.size() && i < rhs.cookieUnits.size(); ++i) {
            c.cookieUnits.at(i) += rhs.cookieUnits.at(i);
    }
    c.redistributeUnitsUp();
    return c;
}

CookieNumber operator+(const CookieNumber &lhs, int rhs) {
    CookieNumber r(rhs);
    return lhs + r;
}

CookieNumber operator+(int lhs, const CookieNumber &rhs) {
    CookieNumber l(lhs);
    return l + rhs;
}

/* Multiplication */

CookieNumber operator*(const CookieNumber &lhs, int rhs) {
    return lhs * CookieNumber(rhs);
}

CookieNumber operator*(int lhs, const CookieNumber &rhs) {
    return CookieNumber(lhs) * rhs;
}

CookieNumber operator*(const CookieNumber &lhs, const CookieNumber &rhs) {
    CookieNumber c(lhs);
    for(auto i = CookieNumber(1); i < rhs; ++i)
    {
        c += lhs;
    }
    return c;
}


//    CookieNumber c(lhs);
//    if (c.cookieUnits.size() < rhs.cookieUnits.size())
//        c.cookieUnits.resize(rhs.cookieUnits.size());
//
//    for(auto it = lhs.cookieUnits.begin(); it != lhs.cookieUnits.end(); ++it)
//    {
//        auto i = std::distance(lhs.cookieUnits.begin(), it);
//        if (rhs.cookieUnits.size() > i)
//            c.cookieUnits.at(i) = lhs.cookieUnits.at(i) * rhs.cookieUnits.at(i);
//        else
//            c.cookieUnits.at(i) = lhs.cookieUnits.at(i);
//    }
//    c.redistributeUnitsUp();
//    return c;
//}

/* Substraction */
CookieNumber operator-(const CookieNumber &lhs, const CookieNumber &rhs) {
    CookieNumber c(lhs);
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
                    *it -= std::abs(minus);
                } else {
                    c = CookieNumber(-1);
                    return c;
                }
            } else {
                c = CookieNumber(-1);
                return c;
            }

        }
        else if (minus == 0)
            *it = 0;
        else
            *it = std::abs(minus);

    }

    return c;
}


CookieNumber operator-(const CookieNumber &lhs, int rhs) {
    return lhs - CookieNumber(rhs);
}

CookieNumber operator-(int lhs, const CookieNumber &rhs) {
    return CookieNumber(lhs) - rhs;
}

/* Helpers */
bool CookieNumber::redistributeUnitsUp() {
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

int CookieNumber::getCookieUnits(int unit) {
    if (unit <= cookieUnits.size())
        return static_cast<int>(cookieUnits.at(unit));
    else
        return 0;
}

int CookieNumber::getAmountOfUnits() {
    return cookieUnits.size();
}

void CookieNumber::printArray() const {
    std::string result;
    for (auto it = cookieUnits.begin(); it != cookieUnits.end(); ++it) {
        auto i = std::distance(cookieUnits.begin(), it);
        result += std::to_string(i) + "=" + std::to_string(*it) + "; ";
    }
    std::cout << "\n" << result << "\n";
}

/* Assignment */

CookieNumber &CookieNumber::operator+=(const CookieNumber &rhs) {
    *this = *this + rhs;
    return *this;
}

CookieNumber &CookieNumber::operator-=(const CookieNumber &rhs) {
    *this = *this - rhs;
    return *this;
}
CookieNumber &CookieNumber::operator*=(const CookieNumber &rhs) {
    *this = *this * rhs;
    return *this;
}

CookieNumber &CookieNumber::operator+=(int rhs) {
    *this = *this + CookieNumber(rhs);
    return *this;
}

CookieNumber &CookieNumber::operator-=(int rhs) {
    *this = *this - CookieNumber(rhs);
    return *this;
}

CookieNumber &CookieNumber::operator*=(int rhs) {
    *this = *this * CookieNumber(rhs);
    return *this;
}

CookieNumber &CookieNumber::operator++() {
    *this = *this + 1;
    return *this;
}

CookieNumber &CookieNumber::operator--() {
    *this = *this - 1;
}

CookieNumber CookieNumber::operator++(int) {
    CookieNumber tmp(*this);
    ++(*this);
    return tmp;
}

CookieNumber CookieNumber::operator--(int) {
    CookieNumber tmp(*this);
    --(*this);
    return tmp;
}

