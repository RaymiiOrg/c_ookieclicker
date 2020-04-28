//
// Created by remy on 26-04-20.
//

#include <iostream>
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

std::ostream &operator<<(std::ostream &os, const CookieNumber2 &number) {
    for (size_t i = 0; i < number.cookieUnits.size(); ++i)
        os << std::to_string(i) << "_" << number.cookieUnits.at(i) << "; ";

    return os;
}

CookieNumber2 operator+(const CookieNumber2 &c1, const CookieNumber2 &c2) {
    CookieNumber2 c(c1);
    if (c.cookieUnits.size() < c2.cookieUnits.size())
        c.cookieUnits.resize(c2.cookieUnits.size());
    for(size_t i = 0; i < c.cookieUnits.size(); ++i) {
        c.cookieUnits.at(i) += c2.cookieUnits.at(i);
    }
    c.redistributeUnitsUp();
    return c;
}



CookieNumber2::CookieNumber2(int first, int kilo, int mega, int giga, int tera, int peta, int exa, int zetta,
                             int yotta) : CookieNumber2() {
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
        return cookieUnits.at(unit);
    else
        return 0;
}

bool CookieNumber2::redistributeUnitsUp() {
    int limit = 1000;
    for (size_t i = 0; i < cookieUnits.size(); ++i) {
        auto modulus = cookieUnits.at(i) % limit;
        auto fitsInTimes = (double)(cookieUnits.at(i) - modulus) / limit;
        if (fitsInTimes > 0) {
//            std::cout << "mod: " << modulus << "; times: " << fitsInTimes << "; " << std::endl;
//            std::cout << fitsInTimes << "*" << limit << "==" << fitsInTimes * limit << std::endl;
//            std::cout << "keep: " << cookieUnits.at(i) - (fitsInTimes * limit) << std::endl;
            if(i == cookieUnits.size()-1) {
                cookieUnits.push_back(fitsInTimes);
            } else {
                cookieUnits.at(i + 1) += fitsInTimes;
            }
            cookieUnits.at(i) -= (fitsInTimes * limit);
        }
    }
    return true;
}

int CookieNumber2::getAmountOfUnits() {
    return cookieUnits.size();
}

CookieNumber2::CookieNumber2(const CookieNumber2 &c) = default;