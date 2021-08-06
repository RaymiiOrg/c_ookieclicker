/**
    Copyright 2021  - Remy van Elst - https://raymii.org
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef C_OOKIECLIKER_COOKIENUMBERS_H
#define C_OOKIECLIKER_COOKIENUMBERS_H

#include <sstream>
#include <vector>
#include <type_traits>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "cmakeConfig.h"


#ifdef USEBOOST_MPP
#include "boost/multiprecision/cpp_dec_float.hpp"
#include "boost/serialization/nvp.hpp"
using CookieNumber = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<0>>;
#else
#include "RegularCookieNumber.h"
using CookieNumber = RegularCookieNumber<long double>;
#endif


class CookieNumberPrinter {
private:

    static std::vector<std::string> cookieNumberNames() {
        std::vector<std::string> allCookieNumberNames{"thousand", "million", "billion", "trillion", "quadrillion",
                                                      "quintillion", "sextillion", "septillion", "octillion",
                                                      "nonillion"};
        std::vector<std::string> prefixes{"", "un", "duo", "tre", "quattuor", "quin", "sex", "septen", "octo", "novem"};
        std::vector<std::string> suffixes{"decillion", "vigintillion", "trigintillion", "quadragintillion",
                                          "quinquagintillion", "sexagintillion", "septuagintillion", "octogintillion",
                                          "nonagintillion", "centillion", "unviginticent", "unsexagintacent", "ducent",
                                          "trecent", "duotrigintatrecent", "quadringent", "quingent", "sescent",
                                          "septuagintisescent",
                                          "septingent", "octingent", "nongent", "millillion", "dumill",
                                          "dumillinonagintanongent",
                                          "trimill", "trimilliduotrigintatrecent", "trimillisexoctogintaoctingent",
                                          "quadrimill",
                                          "quadrimilliquattuordecicent", "quinmill", "sexmill", "septimill", "octimill",
                                          "nonimill",
                                          "myr", "decimilliquinsexagintasescent", "dumyr",
                                          "unquadragintamilliunquinquagintacent",
                                          "centimill", "micr", "nan", "pic", "femt", "att", "zept", "yoct",
                                          " a", " b", " c", " d", " e", " f", " g", " h",
                                          " i"," j", " k", " l", " m", " n", " o", " p", " q",
                                          " r", " s", " t", " u", " v", " w", " x", " y", " z",
                                          " aa", " ab", " ac", " ad", " ae", " af", " ag", " ah",
                                          " ai", " aj", " ak", " al", " am", " an", " ao", " ap", " aq",
                                          " ar", " as", " at", " au", " av", " aw", " ax", " ay", " az",
                                          " ba", " bb", " bc", " bd", " be", " bf", " bg", " bh",
                                          " bi", " bj", " bk", " bl", " bm", " bn", " bo", " bp", " bq",
                                          " br", " bs", " bt", " bu", " bv", " bw", " bx", " by", " bz",
                                          " ca", " cb", " cc", " cd", " ce", " cf", " cg", " ch",
                                          " ci", " cj", " ck", " cl", " cm", " cn", " co", " cp", " cq",
                                          " cr", " cs", " ct", " cu", " cv", " cw", " cx", " cy", " cz",
                                          " da", " db", " dc", " dd", " de", " df", " dg", " dh",
                                          " di", " dj", " dk", " dl", " dm", " dn", " do", " dp", " dq",
                                          " dr", " ds", " dt", " du", " dv", " dw", " dx", " dy", " dz",
                                          " ea", " eb", " ec", " ed", " ee", " ef", " eg", " eh",
                                          " ei", " ej", " ek", " el", " em", " en", " eo", " ep", " eq",
                                          " er", " es", " et", " eu", " ev", " ew", " ex", " ey", " ez",
                                          " fa", " fb", " fc", " fd", " fe", " ff", " fg", " fh",
                                          " fi", " fj", " fk", " fl", " fm", " fn", " fo", " fp", " fq",
                                          " fr", " fs", " ft", " fu", " fv", " fw", " fx", " fy", " fz",
                                          " ga", " gb", " gc", " gd", " ge", " gf", " gg", " gh",
                                          " gi", " gj", " gk", " gl", " gm", " gn", " go", " gp", " gq",
                                          " gr", " gs", " gt", " gu", " gv", " gw", " gx", " gy", " gz",
                                          " ( probably will never get to these suffixes, ) ",
                                          " ( otherwise you're an awesome player! ) ",
                                          " ( please send me an email with a screenshot! ) ",
                                          " ( Psalm 121, KJV ) ",
                                          " ( 1 I will lift up mine eyes unto the hills, from whence cometh my help. ) ",
                                          " ( 2 My help cometh from the Lord, which made heaven and earth. ) ",
                                          " ( 3 He will not suffer thy foot to be moved: he that keepeth thee will not slumber. ) ",
                                          " ( 4 Behold, he that keepeth Israel shall neither slumber nor sleep. ) ",
                                          " ( 5 The Lord is thy keeper: the Lord is thy shade upon thy right hand. ) ",
                                          " ( 6 The sun shall not smite thee by day, nor the moon by night. ) ",
                                          " ( 7 The Lord shall preserve thee from all evil: he shall preserve thy soul. ) ",
                                          " ( 8 The Lord shall preserve thy going out and thy coming in from this time forth, and even for evermore. ) ",
        };
        for (const auto &suffix : suffixes) {
            for (const auto &prefix : prefixes) {
                std::string newString = prefix;
                newString.append(suffix);
                allCookieNumberNames.push_back(newString);
            }
        }
        return allCookieNumberNames;
    };

public:
    static void removeTrailingZeroes(std::string &integerpart) {
        integerpart.erase(integerpart.find_last_not_of('0') + 1, std::string::npos);
    }

    static void removeLeadingZeroes(std::string &integerpart) {
        integerpart.erase(0, std::min(integerpart.find_first_not_of('0'), integerpart.size() - 1));
    }

    static std::pair<std::string, std::string> splitStringNumber(const std::string &largeNumber) {
        std::istringstream iss(largeNumber);
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(iss, token, '.')) {
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }

        std::string integerpart;
        std::string fractionalpart;
        switch (tokens.size()) {
            case 1:
                integerpart = tokens.at(0);
                break;
            case 2:
                integerpart = tokens.at(0);
                fractionalpart = tokens.at(1);
                break;
            default:
                integerpart = largeNumber;
                break;
        }
        removeTrailingZeroes(fractionalpart);

        return {integerpart, fractionalpart};
    }

    template<typename T>
    std::string print(const T &c) const {
        size_t base(0);
        std::string returnString;
        std::string cAsString = c.str(0, std::ios_base::fixed);
        T tmp = c;
        T smallerTmp = c;
        std::string suffix;

        if (tmp >= T(1000000)) {
            tmp /= T(1000);
#ifdef USEBOOST_MPP
            while (boost::multiprecision::round(tmp) >= T(1000)) {
#else
                while (tmp.round() >= T(1000)) {
#endif
                tmp /= T(1000);
                base++;
            }
            if (base >= cookieNumberNames().size()) {
                // poor man's string to pseudo-scientific notation
                size_t len = cAsString.size() - 1;
                std::string beforeDot = cAsString.substr(0, 3);
                std::string afterDot = cAsString.substr(4, 3);
                std::stringstream result;
                result << beforeDot << "." << afterDot << "e+" << std::to_string(len) << " (too large for a suffix) ";
                return result.str();
            } else {
                suffix = cookieNumberNames().at(base);
            }
            smallerTmp = ((tmp * T(1000)) / T(1000));
        }

        std::string smallerTmpAsString = smallerTmp.str(0, std::ios_base::fixed);
        auto splitString = splitStringNumber(smallerTmpAsString);
        std::string integerpart = splitString.first;
        std::string fractionalpart = splitString.second.substr(0,1);

        returnString.append(integerpart);
        if (base == 0 && !fractionalpart.empty() && fractionalpart.at(0) != '0') {
            returnString.append(".");
            returnString.append(fractionalpart);
        } else if (base > 0) {
            std::string next3Numbers = cAsString.substr(integerpart.size(), 3);
            removeTrailingZeroes(next3Numbers);
            if (!next3Numbers.empty()) {
                returnString.append(",");
                returnString.append(next3Numbers);
            }
        }

        if (!suffix.empty()) {
            returnString.append(" ");
            returnString.append(suffix);
        }
        return returnString;
    }

};

typedef CookieNumberPrinter cnp;

static const CookieNumberPrinter cp;

#endif //C_OOKIECLIKER_COOKIENUMBERS_H
