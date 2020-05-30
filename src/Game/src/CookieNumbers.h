//
// Created by remy on 23-05-20.
//

#ifndef C_OOKIECLIKER_COOKIENUMBERS_H
#define C_OOKIECLIKER_COOKIENUMBERS_H

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

typedef boost::multiprecision::cpp_int CookieNumber;
typedef boost::multiprecision::cpp_dec_float_50 CookieFloater;
namespace game {
    const int gameVersion = 102;
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
    std::string print(const CookieNumber &c);
};

typedef CookieNumberPrinter cnp;

#endif //C_OOKIECLIKER_COOKIENUMBERS_H
