#ifndef C_OOKIECLIKER_REGULARCOOKIENUMBER_H
#define C_OOKIECLIKER_REGULARCOOKIENUMBER_H


#include <sstream>
#include <vector>
#include <type_traits>
#include <iostream>
#include <cmath>
#include <iomanip>

template<typename T>
class RegularCookieNumber {
    static_assert(std::is_arithmetic<T>::value, "needs arithmetic T");
    T _value;
public:
    RegularCookieNumber(T value) : _value(value) {};

    RegularCookieNumber() : _value(0) {};

    RegularCookieNumber(const std::string &value) {
        try {
            _value = std::stold(value);
        } catch (const std::out_of_range &e) {
            _value = 0;
        }
    };

    [[nodiscard]] std::string str(std::intmax_t digits, std::ios_base::fmtflags f) const {
        std::ostringstream result;
        result.precision(digits);
        result.setf(f);
        result.fill('0');
        result << std::to_string(_value);
        return result.str();
    }

    RegularCookieNumber pow(const RegularCookieNumber &rhs) {
        return std::pow(_value, rhs._value);
    }

    RegularCookieNumber ceil() {
        return std::ceil(_value);
    }

    RegularCookieNumber round() {
        return std::round(_value);
    }

    RegularCookieNumber &operator*=(const RegularCookieNumber &rhs) {
        T newValue = _value * rhs._value;
        _value = newValue;
        return *this;
    }

    RegularCookieNumber &operator*=(int rhs) {
        T newValue = _value * rhs;
        _value = newValue;
        return *this;
    }

    RegularCookieNumber &operator+=(const RegularCookieNumber &rhs) {
        T newValue = _value + rhs._value;
        _value = newValue;
        return *this;
    }

    RegularCookieNumber &operator-=(const RegularCookieNumber &rhs) {
        T newValue = _value - rhs._value;
        _value = newValue;
        return *this;
    }

    RegularCookieNumber &operator/=(const RegularCookieNumber &rhs) {
        T newValue = _value / rhs._value;
        _value = newValue;
        return *this;
    }

    RegularCookieNumber &operator++() {
        _value++;
        return *this;
    }

    RegularCookieNumber operator++(int) {
        RegularCookieNumber old = *this;
        operator++();
        return old;
    }

    RegularCookieNumber &operator--() {
        _value--;
        return *this;
    }

    RegularCookieNumber operator--(int) {
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
        os << number._value;
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

template<typename T>
RegularCookieNumber<T> operator*(RegularCookieNumber<T> lhs, const RegularCookieNumber<T> &rhs) {
    return lhs *= rhs;
}

template<typename T>
RegularCookieNumber<T> operator*(RegularCookieNumber<T> lhs, int rhs) {
    return lhs *= rhs;
}

template<typename T>
RegularCookieNumber<T> operator+(RegularCookieNumber<T> lhs, const RegularCookieNumber<T> &rhs) {
    return lhs += rhs;
}

template<typename T>
RegularCookieNumber<T> operator-(RegularCookieNumber<T> lhs, const RegularCookieNumber<T> &rhs) {
    return lhs -= rhs;
}

template<typename T>
RegularCookieNumber<T> operator/(RegularCookieNumber<T> lhs, const RegularCookieNumber<T> &rhs) {
    return lhs /= rhs;
}


#endif //C_OOKIECLIKER_REGULARCOOKIENUMBER_H
