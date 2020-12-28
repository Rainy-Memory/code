//
// Created by Rainy Memory on 2020/12/16.
//

#include "Rational.h"
#include <iostream>

Rational::Rational() : num(1), den(1) {
    ReductFraction();
}

Rational::Rational(int num, int den = 1) : num(num), den(den) {
    ReductFraction();
}

Rational::Rational(const Rational &r) : num(r.num), den(r.den) {
    ReductFraction();
}

Rational::Rational(int _num) : num(_num), den(1) {
    ReductFraction();
}

Rational::~Rational() {

}

void Rational::ReductFraction() {
    if(num==0){
        den=1;
    }
    else {
        for (int temp = num > den ? den : num; temp >= 0; temp--) {
            if (num % temp == 0 & den % temp == 0) {
                num /= temp;
                den /= temp;
                break;
            }
        }
    }
}

int Rational::getNum() const {
    return num;
}

void Rational::setNum(int num) {
    Rational::num = num;
}

int Rational::getDen() const {
    return den;
}

void Rational::setDen(int den) {
    Rational::den = den;
}

bool Rational::operator==(const Rational &rhs) const {
    return num == rhs.num && den == rhs.den;
}

bool Rational::operator!=(const Rational &rhs) const {
    return !(rhs == *this);
}

bool Rational::operator<(const Rational &rhs) const {
    return num * rhs.den < den * rhs.num;
}

bool Rational::operator>(const Rational &rhs) const {
    return rhs < *this;
}

bool Rational::operator<=(const Rational &rhs) const {
    return !(rhs < *this);
}

bool Rational::operator>=(const Rational &rhs) const {
    return !(*this < rhs);
}

bool Rational::operator!() const{
    if(num==0)return true;
    else return false;
}

Rational Rational::operator-() const {
    return Rational(-num, den);
}

Rational Rational::operator+(const Rational &r) const {
    return Rational(num * r.den + den * r.num, den * r.den);
}

Rational Rational::operator-(const Rational &r) const {
    Rational temp = (*this) + (-r);
    return temp;
}

Rational Rational::operator*(const Rational &r) const {
    return Rational(num * r.num, den * r.den);
}

Rational Rational::operator/(const Rational &r) const {
    return Rational(num * r.den, den * r.num);
}

Rational &Rational::operator++() {
    //std::cout<<"pre++"<<std::endl;
    num += den;
    return *this;
}

Rational Rational::operator++(int) {
    //std::cout<<"suf++"<<std::endl;
    Rational temp = *this;
    num += den;
    return temp;
}

Rational &Rational::operator--() {
    num -= den;
    return *this;
}

Rational Rational::operator--(int) {
    Rational temp = *this;
    num -= den;
    return temp;
}

std::ostream &operator<<(std::ostream &os, const Rational &r) {
    if (r.den != 1)os << r.num << "/" << r.den;
    else os << r.num;
    return os;
}

std::istream &operator>>(std::istream &is, Rational &r) {
    char temp;
    is >> r.num >> temp >> r.den;
    r.ReductFraction();
    return is;
}

Rational::operator double() {
    double num_ = num, den_ = den;
    return num_ / den_;
}
