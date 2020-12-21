//
// Created by Rainy Memory on 2020/12/16.
//

#ifndef CODE_RATIONAL_H
#define CODE_RATIONAL_H


#include <ostream>

class Rational {
private:
    int num;
    int den;
    
    void ReductFraction();

public:
    Rational();
    
    Rational(int num, int den);
    
    Rational(const Rational &r);
    
    Rational(int num);
    
    virtual ~Rational();
    
    int getNum() const;
    
    void setNum(int num);
    
    int getDen() const;
    
    void setDen(int den);
    
    bool operator==(const Rational &rhs) const;
    
    bool operator!=(const Rational &rhs) const;
    
    bool operator<(const Rational &rhs) const;
    
    bool operator>(const Rational &rhs) const;
    
    bool operator<=(const Rational &rhs) const;
    
    bool operator>=(const Rational &rhs) const;
    
    Rational operator-() const;
    
    Rational operator+(const Rational &r) const;
    
    Rational operator-(const Rational &r) const;
    
    Rational operator*(const Rational &r) const;
    
    Rational operator/(const Rational &r) const;
    
    Rational &operator++();
    
    Rational operator++(int);
    
    Rational &operator--();
    
    Rational operator--(int);
    
    friend std::ostream &operator<<(std::ostream &os, const Rational &rational);
    
    friend std::istream &operator>>(std::istream &is,Rational &r);
    
    operator double();
};


#endif //CODE_RATIONAL_H
