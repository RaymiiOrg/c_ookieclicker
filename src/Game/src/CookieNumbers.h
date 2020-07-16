//
// Created by remy on 23-05-20.
//

#ifndef C_OOKIECLIKER_COOKIENUMBERS_H
#define C_OOKIECLIKER_COOKIENUMBERS_H

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

typedef boost::multiprecision::cpp_int CookieInt;
typedef boost::multiprecision::cpp_dec_float_50 CookieFloater;
typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<0>> CookieNumber;

namespace game {
    const int gameVersion = 105;
}

class CookieNumberPrinter {
private:
    std::vector<std::string> cookieNumberNames {"", "unit", "ten", "hundred",
    " thousand", " thousand", " thousand", //1, 10, 100 thousand
    " million", " million", " million", // 1, 10, 100 million
    " billion", " billion", " billion",
    " trillion", " trillion", " trillion",
    " quadrillion", " quadrillion", " quadrillion",
    " quintillion", " quintillion", " quintillion",
    " sextillion", " sextillion", " sextillion",
    " septillion", " septillion", " septillion",
    " octillion", " octillion", " octillion",
    " nonillion", " nonillion", " nonillion",
    " decillion", " decillion", " decillion",
    " undecillion", " undecillion", " undecillion",
    " duodecillion", " duodecillion", " duodecillion",
    " tredecillion", " tredecillion", " tredecillion",
    " quattuordecillion", " quattuordecillion", " quattuordecillion",
    " quindecillion", " quindecillion", " quindecillion",
    " sexdecillion", " sexdecillion", " sexdecillion",
    " septendecillion", " septendecillion", " septendecillion",
    " octodecillion", " octodecillion", " octodecillion",
    " novemdecillion", " novemdecillion", " novemdecillion",
    " vigintillion", " vigintillion", " vigintillion",
    " centillion", " centillion", " centillion",
    "a", "a", "a",
    "b", "b", "b",
    "c", "c", "c",
    "d", "d", "d",
    "e", "e", "e",
    "f", "f", "f",
    "g", "g", "g",
    "h", "h", "h",
    "i", "i", "i",
    "j", "j", "j",
    "k", "k", "k",
    "l", "l", "l",
    "m", "m", "m",
    "n", "n", "n",
    "o", "o", "o",
    "p", "p", "p",
    "q", "q", "q",
    "r", "r", "r",
    "s", "s", "s",
    "t", "t", "t",
    "u", "u", "u",
    "v", "v", "v",
    "w", "w", "w",
    "x", "x", "x",
    "y", "y", "y",
    "z", "z", "z",
    "aa", "aa", "aa",
    "bb", "bb", "bb",
    "cc", "cc", "cc",
    "dd", "dd", "dd",
    "ee", "ee", "ee",
    "ff", "ff", "ff",
    "gg", "gg", "gg",
    "hh", "hh", "hh",
    "ii", "ii", "ii",
    "jj", "jj", "jj",
    "kk", "kk", "kk",
    "ll", "ll", "ll",
    "mm", "mm", "mm",
    "nn", "nn", "nn",
    "oo", "oo", "oo",
    "pp", "pp", "pp",
    "qq", "qq", "qq",
    "rr", "rr", "rr",
    "ss", "ss", "ss",
    "tt", "tt", "tt",
    "uu", "uu", "uu",
    "vv", "vv", "vv",
    "ww", "ww", "ww",
    "xx", "xx", "xx",
    "yy", "yy", "yy",
    "zz", "zz", "zz",
    "aaa", "aaa", "aaa",
    "bbb", "bbb", "bbb",
    "ccc", "ccc", "ccc",
    "ddd", "ddd", "ddd",
    "eee", "eee", "eee",
    "fff", "fff", "fff",
    "ggg", "ggg", "ggg",
    "hhh", "hhh", "hhh",
    "iii", "iii", "iii",
    "jjj", "jjj", "jjj",
    "kkk", "kkk", "kkk",
    "lll", "lll", "lll",
    "mmm", "mmm", "mmm",
    "nnn", "nnn", "nnn",
    "ooo", "ooo", "ooo",
    "ppp", "ppp", "ppp",
    "qqq", "qqq", "qqq",
    "rrr", "rrr", "rrr",
    "sss", "sss", "sss",
    "ttt", "ttt", "ttt",
    "uuu", "uuu", "uuu",
    "vvv", "vvv", "vvv",
    "www", "www", "www",
    "xxx", "xxx", "xxx",
    "yyy", "yyy", "yyy",
    "zzz", "zzz", "zzz",};
public:
    /**
     *  Print a boost multiprecision cpp_int or cpp_dec_float in "idle game style"
     *  like, 1 billion, 250 prefixA, 3rr, etc.
     */
    template<typename T>
    std::string print(const T &c) const  {
        // convert the entire number to a string, without scientific notation.
        // 1.1 becomes:
        // 1.100000000000000000000000000000000
        // 29732982334867582149325438874912272258649497973483149622529685538613555010863828154687010115074346034315149633447312785822266082974277863522538340841432531289626639929448668816617338316564681262640080.0
        // becomes:
        // 29732982334867582149325438874912272258640000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.0000000000000000000000000000000000000000
        std::string entireCookieNumber = c.str(0, std::ios_base::fixed);

        // split the number into the integer and fractional string parts (before and after the .)
        std::istringstream iss(entireCookieNumber);
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(iss, token, '.')) {
            if (!token.empty())
                tokens.push_back(token);
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
                integerpart = entireCookieNumber;
                break;
        }

        // the length of the integer part of a boost cpp_dec_float
        // is of importance for us, (what suffix to print) but with
        // our level of precision, the number contains mostly zeroes,
        // so we only remove trailing zero's from the fractional part.
        // we're not interested in those for printing.
        removeTrailingZeroes(fractionalpart);

        // printing logic starts here. We cant have negative amounts of cookies.
        if (c <= 0) {
            return "0";
        } else if (integerpart.length() <= 5) {
            // up until the thousands we're interested in the fractional part
            if (fractionalpart.length() > 0 && std::stoi(fractionalpart.substr(0,1)) > 0) {
                return integerpart + "." + fractionalpart.at(0);
            } else {
                // don't print 2. if number is 2.0. just print 2.
                return integerpart;
            }
        } else if (cookieNumberNames.size()-1 > (integerpart.length()-2)) {
            // if we get bigger we want named numbers (75 billion, 229n, etc).
            // nobody cares about after the fractional part here...
            std::string returnString;
            returnString += integerpart.at(0);
            if (cookieNumberNames.at(integerpart.length()-1) == cookieNumberNames.at(integerpart.length())) {
                returnString += integerpart.at(1);
            }
            if (cookieNumberNames.at(integerpart.length()-2) == cookieNumberNames.at(integerpart.length())) {
                returnString += integerpart.at(2);
            }

            auto lengthBeforeComma = returnString.length();

            returnString += ",";

            if (integerpart.length() > lengthBeforeComma)
                returnString += integerpart.at(lengthBeforeComma);
            if (integerpart.length() > (lengthBeforeComma) + 1)
                returnString += integerpart.at((lengthBeforeComma) + 1);
            if (integerpart.length() > (lengthBeforeComma) + 2 )
                returnString += integerpart.at(lengthBeforeComma + 2);

            returnString += cookieNumberNames.at(integerpart.length());
            return returnString;
        } else {
            return integerpart += " amazingly big amount for which I did not define a suffix yet ";
        }
    }

    static void removeTrailingZeroes(std::string &integerpart) { integerpart.erase (integerpart.find_last_not_of('0') + 1, std::string::npos ); }

    static void removeLeadingZeroes(std::string &integerpart) { integerpart.erase(0, std::min(integerpart.find_first_not_of('0'), integerpart.size() - 1)); }
};


typedef CookieNumberPrinter cnp;

#endif //C_OOKIECLIKER_COOKIENUMBERS_H
