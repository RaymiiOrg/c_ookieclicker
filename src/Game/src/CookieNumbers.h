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
#include "cmakeConfig.h"

template <typename T>
class RegularCookieNumber {
    static_assert(std::is_arithmetic <T>::value, "needs arithmetic T");
    T _value;
public:
    RegularCookieNumber(T value) : _value(value) {};
    RegularCookieNumber() : _value(0) {};
    RegularCookieNumber(const std::string& value) {
        try {
            _value = std::stoll(value);
        } catch (const std::invalid_argument& e) {
            std::cerr << "value: " << value << " throws: " << e.what();
            _value = std::stold(value);
        } catch (const std::out_of_range& e) {
            std::cerr << "value: " << value << " throws: " << e.what() << ". value is now 0.";
            _value = 0;
        }
    };
    [[nodiscard]] std::string str(std::intmax_t digits, std::ios_base::fmtflags f) const {
        std::ostringstream result;
        result.width(digits);
        result.setf(f);
        result.fill('0');
        result << std::to_string(f);
        return result.str();
    }

    RegularCookieNumber pow(const RegularCookieNumber& rhs) {
        return std::pow(_value, rhs._value);
    }

    RegularCookieNumber& operator*= (const RegularCookieNumber &rhs) {
        T newValue = _value * rhs._value;
        _value = newValue;
        return *this;
    }

    RegularCookieNumber& operator*= (int rhs) {
        T newValue = _value * rhs;
        _value = newValue;
        return *this;
    }

    RegularCookieNumber& operator+= (const RegularCookieNumber &rhs) {
        T newValue = _value + rhs._value;
        _value = newValue;
        return *this;
    }

    RegularCookieNumber& operator-= (const RegularCookieNumber &rhs) {
        T newValue = _value - rhs._value;
        _value = newValue;
        return *this;
    }

    RegularCookieNumber& operator/= (const RegularCookieNumber &rhs) {
        T newValue = _value / rhs._value;
        _value = newValue;
        return *this;
    }

    RegularCookieNumber& operator++()
    {
        return *this;
    }

    RegularCookieNumber operator++(int)
    {
        RegularCookieNumber old = *this;
        operator++();
        return old;
    }

    RegularCookieNumber& operator--()
    {
        return *this;
    }

    RegularCookieNumber operator--(int)
    {
        RegularCookieNumber old = *this;
        operator--();
        return old;
    }

    bool operator==(const RegularCookieNumber &rhs) const {
        return _value == rhs._value;
    }

    bool operator<(const RegularCookieNumber &rhs) const {
        return _value < rhs._value;
    }

    friend std::ostream &operator<<(std::ostream &os, const RegularCookieNumber &number) {
        os << "value: " << number._value;
        return os;
    }

    bool operator>(const RegularCookieNumber &rhs) const {
        return rhs < *this;
    }

    bool operator!=(const RegularCookieNumber &rhs) const {
        return !(rhs == *this);
    }

    bool operator<=(const RegularCookieNumber &rhs) const {
        return rhs >= *this;
    }

    bool operator>=(const RegularCookieNumber &rhs) const {
        return !(*this < rhs);
    }

};

template <typename T>
RegularCookieNumber<T> operator*(RegularCookieNumber<T> lhs, const RegularCookieNumber<T>& rhs)
{
    return lhs *= rhs;
}

template <typename T>
RegularCookieNumber<T> operator*(RegularCookieNumber<T> lhs, int rhs)
{
    return lhs *= rhs;
}

template <typename T>
RegularCookieNumber<T> operator+(RegularCookieNumber<T> lhs, const RegularCookieNumber<T>& rhs)
{
    return lhs += rhs;
}

template <typename T>
RegularCookieNumber<T> operator-(RegularCookieNumber<T> lhs, const RegularCookieNumber<T>& rhs)
{
    return lhs -= rhs;
}

template <typename T>
RegularCookieNumber<T> operator/(RegularCookieNumber<T> lhs, const RegularCookieNumber<T>& rhs)
{
    return lhs /= rhs;
}

#ifdef USEBOOST_MPP
    #include <boost/serialization/nvp.hpp>
    #include <boost/multiprecision/cpp_dec_float.hpp>
    #include <boost/multiprecision/cpp_int.hpp>
    typedef boost::multiprecision::cpp_int CookieInt;
    typedef boost::multiprecision::cpp_dec_float_50 CookieFloater;
    typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<0>> CookieNumber;
#else
        typedef RegularCookieNumber<unsigned long long> CookieInt;
        typedef RegularCookieNumber<long double> CookieFloater;
        typedef RegularCookieNumber<long double> CookieNumber;
#endif


class CookieNumberPrinter
{
private:
    std::vector<std::string> cookieNumberNames {
        "",
        "unit",
        "ten",
        "hundred",
        " thousand",
        " thousand",
        " thousand", //1, 10, 100 thousand
        " million",
        " million",
        " million", // 1, 10, 100 million
        " billion",
        " billion",
        " billion",
        " trillion",
        " trillion",
        " trillion",
        " quadrillion",
        " quadrillion",
        " quadrillion",
        " quintillion",
        " quintillion",
        " quintillion",
        " sextillion",
        " sextillion",
        " sextillion",
        " septillion",
        " septillion",
        " septillion",
        " octillion",
        " octillion",
        " octillion",
        " nonillion",
        " nonillion",
        " nonillion",
        " decillion",
        " decillion",
        " decillion",
        " undecillion",
        " undecillion",
        " undecillion",
        " duodecillion",
        " duodecillion",
        " duodecillion",
        " tredecillion",
        " tredecillion",
        " tredecillion",
        " quattuordecillion",
        " quattuordecillion",
        " quattuordecillion",
        " quindecillion",
        " quindecillion",
        " quindecillion",
        " sexdecillion",
        " sexdecillion",
        " sexdecillion",
        " septendecillion",
        " septendecillion",
        " septendecillion",
        " octodecillion",
        " octodecillion",
        " octodecillion",
        " novemdecillion",
        " novemdecillion",
        " novemdecillion",
        " vigintillion",
        " vigintillion",
        " vigintillion",
        " centillion",
        " centillion",
        " centillion",
        "a",
        "a",
        "a",
        "b",
        "b",
        "b",
        "c",
        "c",
        "c",
        "d",
        "d",
        "d",
        "e",
        "e",
        "e",
        "f",
        "f",
        "f",
        "g",
        "g",
        "g",
        "h",
        "h",
        "h",
        "i",
        "i",
        "i",
        "j",
        "j",
        "j",
        "k",
        "k",
        "k",
        "l",
        "l",
        "l",
        "m",
        "m",
        "m",
        "n",
        "n",
        "n",
        "o",
        "o",
        "o",
        "p",
        "p",
        "p",
        "q",
        "q",
        "q",
        "r",
        "r",
        "r",
        "s",
        "s",
        "s",
        "t",
        "t",
        "t",
        "u",
        "u",
        "u",
        "v",
        "v",
        "v",
        "w",
        "w",
        "w",
        "x",
        "x",
        "x",
        "y",
        "y",
        "y",
        "z",
        "z",
        "z",
        "aa",
        "aa",
        "aa",
        "bb",
        "bb",
        "bb",
        "cc",
        "cc",
        "cc",
        "dd",
        "dd",
        "dd",
        "ee",
        "ee",
        "ee",
        "ff",
        "ff",
        "ff",
        "gg",
        "gg",
        "gg",
        "hh",
        "hh",
        "hh",
        "ii",
        "ii",
        "ii",
        "jj",
        "jj",
        "jj",
        "kk",
        "kk",
        "kk",
        "ll",
        "ll",
        "ll",
        "mm",
        "mm",
        "mm",
        "nn",
        "nn",
        "nn",
        "oo",
        "oo",
        "oo",
        "pp",
        "pp",
        "pp",
        "qq",
        "qq",
        "qq",
        "rr",
        "rr",
        "rr",
        "ss",
        "ss",
        "ss",
        "tt",
        "tt",
        "tt",
        "uu",
        "uu",
        "uu",
        "vv",
        "vv",
        "vv",
        "ww",
        "ww",
        "ww",
        "xx",
        "xx",
        "xx",
        "yy",
        "yy",
        "yy",
        "zz",
        "zz",
        "zz",
        "aaa",
        "aaa",
        "aaa",
        "bbb",
        "bbb",
        "bbb",
        "ccc",
        "ccc",
        "ccc",
        "ddd",
        "ddd",
        "ddd",
        "eee",
        "eee",
        "eee",
        "fff",
        "fff",
        "fff",
        "ggg",
        "ggg",
        "ggg",
        "hhh",
        "hhh",
        "hhh",
        "iii",
        "iii",
        "iii",
        "jjj",
        "jjj",
        "jjj",
        "kkk",
        "kkk",
        "kkk",
        "lll",
        "lll",
        "lll",
        "mmm",
        "mmm",
        "mmm",
        "nnn",
        "nnn",
        "nnn",
        "ooo",
        "ooo",
        "ooo",
        "ppp",
        "ppp",
        "ppp",
        "qqq",
        "qqq",
        "qqq",
        "rrr",
        "rrr",
        "rrr",
        "sss",
        "sss",
        "sss",
        "ttt",
        "ttt",
        "ttt",
        "uuu",
        "uuu",
        "uuu",
        "vvv",
        "vvv",
        "vvv",
        "www",
        "www",
        "www",
        "xxx",
        "xxx",
        "xxx",
        "yyy",
        "yyy",
        "yyy",
        "zzz",
        "zzz",
        "zzz",
    };

public:
    /**
     *  Print a boost multiprecision cpp_int or cpp_dec_float in "idle game style"
     *  like, 1 billion, 250 prefixA, 3rr, etc.
     */
    template <typename T>
    std::string print(const T &c) const
    {
        // convert the entire number to a string, without scientific notation.
        // 1.1 becomes:
        // 1.100000000000000000000000000000000
        // 29732982334867582149325438874912272258649497973483149622529685538613555010863828154687010115074346034315149633447312785822266082974277863522538340841432531289626639929448668816617338316564681262640080.0
        // becomes:
        // 29732982334867582149325438874912272258640000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.0000000000000000000000000000000000000000
        std::string entireCookieNumber = c.str(0, std::ios_base::fixed);

        // split the number into the integer and RegularCookieNumberal string parts (before and after the .)
        std::istringstream iss(entireCookieNumber);
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(iss, token, '.'))
        {
            if (!token.empty())
                tokens.push_back(token);
        }

        std::string integerpart;
        std::string RegularCookieNumberalpart;
        switch (tokens.size())
        {
        case 1:
            integerpart = tokens.at(0);
            break;
        case 2:
            integerpart = tokens.at(0);
            RegularCookieNumberalpart = tokens.at(1);
            break;
        default:
            integerpart = entireCookieNumber;
            break;
        }

        // the length of the integer part of a boost cpp_dec_float
        // is of importance for us, (what suffix to print) but with
        // our level of precision, the number contains mostly zeroes,
        // so we only remove trailing zero's from the RegularCookieNumberal part.
        // we're not interested in those for printing.
        removeTrailingZeroes(RegularCookieNumberalpart);

        // printing logic starts here. We cant have negative amounts of cookies.
        if (c <= 0)
        {
            return "0";
        }
        else if (integerpart.length() <= 5)
        {
            // up until the thousands we're interested in the RegularCookieNumberal part
            if (RegularCookieNumberalpart.length() > 0 && std::stoi(RegularCookieNumberalpart.substr(0, 1)) > 0)
            {
                return integerpart + "." + RegularCookieNumberalpart.at(0);
            }
            else
            {
                // don't print 2. if number is 2.0. just print 2.
                return integerpart;
            }
        }
        else if (cookieNumberNames.size() - 1 > (integerpart.length() - 2))
        {
            // if we get bigger we want named numbers (75 billion, 229n, etc).
            // nobody cares about after the RegularCookieNumberal part here...
            std::string returnString;
            returnString += integerpart.at(0);
            if (cookieNumberNames.at(integerpart.length() - 1) == cookieNumberNames.at(integerpart.length()))
            {
                returnString += integerpart.at(1);
            }
            if (cookieNumberNames.at(integerpart.length() - 2) == cookieNumberNames.at(integerpart.length()))
            {
                returnString += integerpart.at(2);
            }

            returnString += cookieNumberNames.at(integerpart.length());
            return returnString;
        }
        else
        {
            return integerpart += " amazingly big amount for which I did not define a suffix yet ";
        }
    }

    static void removeTrailingZeroes(std::string &integerpart) { integerpart.erase(integerpart.find_last_not_of('0') + 1, std::string::npos); }

    static void removeLeadingZeroes(std::string &integerpart) { integerpart.erase(0, std::min(integerpart.find_first_not_of('0'), integerpart.size() - 1)); }
};

typedef CookieNumberPrinter cnp;

static const CookieNumberPrinter cp;

#endif //C_OOKIECLIKER_COOKIENUMBERS_H
