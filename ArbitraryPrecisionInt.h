//
// Created by Rainy Memory on 2020/12/31.
//

#ifndef CODE_ARBITRARYPRECISIONINT_H
#define CODE_ARBITRARYPRECISIONINT_H

#include <string>
#include <cstring>
#include <iostream>

using std::string;
using std::istream;
using std::ostream;
using std::endl;

class DevidedByZero {
};

class ArbitraryPrecisionInt {

private:
    string str;
    int len = 0;
    int *num = nullptr; //reversed
    bool positive = true;

private:
    friend istream &operator>>(istream &is, ArbitraryPrecisionInt &o);
    
    friend ostream &operator<<(ostream &os, const ArbitraryPrecisionInt &o);
    
    friend bool operator==(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2);
    
    friend bool operator!=(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2);
    
    friend bool operator<(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2);
    
    friend bool operator>(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2);
    
    friend bool operator<=(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2);
    
    friend bool operator>=(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2);
    
    friend ArbitraryPrecisionInt operator-(const ArbitraryPrecisionInt &o);
    
    friend ArbitraryPrecisionInt abs(const ArbitraryPrecisionInt &o);
    
    friend ArbitraryPrecisionInt operator+(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2);
    
    friend ArbitraryPrecisionInt operator-(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2);
    
    friend ArbitraryPrecisionInt operator*(const ArbitraryPrecisionInt &o, int o_);//multiple one digit int
    
    friend ArbitraryPrecisionInt operator*(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2);
    
    friend ArbitraryPrecisionInt operator/(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2);
    
    friend ArbitraryPrecisionInt operator%(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2);

public:
    ArbitraryPrecisionInt();
    
    explicit ArbitraryPrecisionInt(int o);
    
    explicit ArbitraryPrecisionInt(double o);
    
    explicit ArbitraryPrecisionInt(bool o);
    
    explicit ArbitraryPrecisionInt(string str);
    
    ArbitraryPrecisionInt(int *o, int size, bool pos);
    
    ArbitraryPrecisionInt(const ArbitraryPrecisionInt &o);
    
    ArbitraryPrecisionInt(ArbitraryPrecisionInt &&o);
    
    ArbitraryPrecisionInt &operator=(const ArbitraryPrecisionInt &o);
    
    ArbitraryPrecisionInt &operator=(ArbitraryPrecisionInt &&o);
    
    ~ArbitraryPrecisionInt();
    
    ArbitraryPrecisionInt operator-();
    
    ArbitraryPrecisionInt &operator+=(const ArbitraryPrecisionInt &o);
    
    ArbitraryPrecisionInt &operator-=(const ArbitraryPrecisionInt &o);
    
    ArbitraryPrecisionInt &operator*=(const ArbitraryPrecisionInt &o);
    
    ArbitraryPrecisionInt &operator/=(const ArbitraryPrecisionInt &o);
    
    ArbitraryPrecisionInt &operator%=(const ArbitraryPrecisionInt &o);
    
    ArbitraryPrecisionInt &operator++();
    
    ArbitraryPrecisionInt operator++(int);
    
    ArbitraryPrecisionInt &operator--();
    
    ArbitraryPrecisionInt operator--(int);
    
    ArbitraryPrecisionInt pow(int power);
    
    ArbitraryPrecisionInt multiple_ten(int bit);
    
    ArbitraryPrecisionInt devide_ten(int bit);
    
    explicit operator int() const;
    
    explicit operator double() const;
    
    explicit operator bool() const;
    
    explicit operator string() const;
};

const ArbitraryPrecisionInt ArbitraryPrecisionIntZero = ArbitraryPrecisionInt(0);

const ArbitraryPrecisionInt ArbitraryPrecisionIntOne = ArbitraryPrecisionInt(1);

#endif //CODE_ARBITRARYPRECISIONINT_H