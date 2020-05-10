//
// Created by remy on 26-04-20.
//

#ifndef C_OOKIECLIKER_CookieNumber_H
#define C_OOKIECLIKER_CookieNumber_H


#include <ostream>
#include <vector>
#include <map>
#include <iomanip>
#include <iostream>

class CookieNumber {
public:
    /* Constructor */
    explicit CookieNumber(int first = 0, int kilo = 0, int mega = 0, int giga = 0, int tera = 0, int peta = 0,
            int exa = 0, int zetta = 0, int yotta = 0);
    /* Copy Constructor */
    CookieNumber(const CookieNumber &c) = default;

    /* getters */
    int getCookieUnits(int unit);
    int getAmountOfUnits();

    /* output */
    friend std::ostream &operator<<(std::ostream &os, const CookieNumber &number);
    void printArray();

    /* comparison */
    bool operator==(const CookieNumber &rhs) const;
    bool operator!=(const CookieNumber &rhs) const;
    bool operator<(const CookieNumber &rhs) const;
    bool operator>(const CookieNumber &rhs) const;
    bool operator<=(const CookieNumber &rhs) const;
    bool operator>=(const CookieNumber &rhs) const;

    /* Addition  */
    friend CookieNumber operator+(const CookieNumber &lhs, const CookieNumber &rhs);
    friend CookieNumber operator+(const CookieNumber &lhs, int rhs);
    friend CookieNumber operator+(int lhs, const CookieNumber &rhs);

    /* Substract */
    friend CookieNumber operator-(const CookieNumber &lhs, const CookieNumber &rhs);
    friend CookieNumber operator-(const CookieNumber &lhs, int rhs);
    friend CookieNumber operator-(int lhs, const CookieNumber &rhs);

    /* Division */

    /* Multiplication */
    friend CookieNumber operator*(const CookieNumber &lhs, const CookieNumber &rhs);
    friend CookieNumber operator*(const CookieNumber &lhs, int rhs);
    friend CookieNumber operator*(int lhs, const CookieNumber &rhs);


    /* Increment & Decrement */
    CookieNumber& operator++(); // prefix
    CookieNumber& operator--(); // prefix
    CookieNumber operator++(int); // postfix
    CookieNumber operator--(int); // postfix


    /* asssignment */
    // default assignment operator= is provided by compiler.
    CookieNumber& operator+= (const CookieNumber &rhs);
    CookieNumber& operator-= (const CookieNumber &rhs);
    CookieNumber& operator*= (const CookieNumber &rhs);
    //CookieNumber& operator/= (const CookieNumber &rhs);
    CookieNumber& operator+= (int rhs);
    CookieNumber& operator-= (int rhs);
    CookieNumber& operator*= (int rhs);
    //CookieNumber& operator/= (const CookieNumber &rhs);

protected:
    std::vector<long long int> cookieUnits {0,0,0,0,0,0,0,0,0};
    int limitPerUnit = 1000;
    bool redistributeUnitsUp();



};


#endif //C_OOKIECLIKER_CookieNumber_H
