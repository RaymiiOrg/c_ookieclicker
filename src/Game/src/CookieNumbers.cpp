//
// Created by remy on 24-05-20.
//
#include "CookieNumbers.h"

std::string CookieNumberPrinter::print(const CookieNumber &c) {
        if (c <= 0) {
            return "0";
        } else if (c >= 1 && c.str().length() <= 13) {
            return c.str();
        } else if (cookieNumberNames.size()-1 > (c.str().length())) {
            std::string retStr;
            retStr += c.str().at(0);
            if (cookieNumberNames.at(c.str().length()-1) == cookieNumberNames.at(c.str().length()))
                retStr += c.str().at(1);
            if (cookieNumberNames.at(c.str().length()-2) == cookieNumberNames.at(c.str().length()))
                retStr += c.str().at(2);
            retStr += cookieNumberNames.at(c.str().length());
            return retStr;
        } else {
            return c.str() += " amazingly big amount for which I did not define a suffix yet ";
        }
    }
