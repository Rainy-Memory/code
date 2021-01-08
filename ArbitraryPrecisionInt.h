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

class DevidedByZero {};

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
    
    ArbitraryPrecisionInt(int o);
    
    ArbitraryPrecisionInt(string str);
    
    ArbitraryPrecisionInt(int *o, int size, bool pos);
    
    ArbitraryPrecisionInt(const ArbitraryPrecisionInt &o);
    
    ArbitraryPrecisionInt &operator=(const ArbitraryPrecisionInt &o);
    
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
};

#endif //CODE_ARBITRARYPRECISIONINT_H