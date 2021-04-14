//
// Created by Rainy Memory on 2021/4/9.
//

#pragma region ArbitraryPrecisionInt

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

ArbitraryPrecisionInt::ArbitraryPrecisionInt() = default;

ArbitraryPrecisionInt::ArbitraryPrecisionInt(int o) {
    if (o == 0) {
        str = "0";
        len = 1;
        num = new int[1];
        num[0] = 0;
        positive = true;
    }
    else {
        positive = true;
        if (o < 0) {
            o *= -1;
            positive = false;
        }
        int temp = o, cnt = 0;
        string tempstr = "";
        while (temp > 0) {
            tempstr += char((temp % 10) + '0');
            temp /= 10;
            cnt++;
        }
        for (int i = tempstr.length() - 1; i >= 0; i--) {
            str += tempstr[i];
        }
        len = cnt;
        num = new int[len];
        for (int i = 0; i < len; i++) {
            num[i] = str[len - i - 1] - '0';
        }
    }
}

ArbitraryPrecisionInt::ArbitraryPrecisionInt(double o) {
    int oo = (int) o;
    *this = ArbitraryPrecisionInt(oo);
}

ArbitraryPrecisionInt::ArbitraryPrecisionInt(bool o) {
    if (o)*this = ArbitraryPrecisionIntOne;
    else *this = ArbitraryPrecisionIntZero;
}

ArbitraryPrecisionInt::ArbitraryPrecisionInt(string str_) {
    if (str_[0] == '-') {
        str_.erase(0, 1);
        str = str_;
        len = str_.length();
        num = new int[len];
        for (int i = 0; i < len; i++) {
            num[i] = str[len - i - 1] - '0';
        }
        positive = false;
    }
    else {
        str = str_;
        len = str_.length();
        num = new int[len];
        for (int i = 0; i < len; i++) {
            num[i] = str[len - i - 1] - '0';
        }
        positive = true;
    }
}

ArbitraryPrecisionInt::ArbitraryPrecisionInt(int *o, int size, bool pos) : len(size), positive(pos) {
    num = new int[len];
    for (int i = 0; i < len; i++) {
        num[i] = o[i];
        str += char(o[len - i - 1] + '0');
    }
}

ArbitraryPrecisionInt::ArbitraryPrecisionInt(const ArbitraryPrecisionInt &o) : str(o.str), len(o.len), positive(o.positive) {
    num = new int[len];
    for (int i = 0; i < len; i++)num[i] = o.num[i];
}

ArbitraryPrecisionInt::ArbitraryPrecisionInt(ArbitraryPrecisionInt &&o) : str(o.str), len(o.len), positive(o.positive) {
    num = o.num;
    o.num = nullptr;
}

ArbitraryPrecisionInt &ArbitraryPrecisionInt::operator=(const ArbitraryPrecisionInt &o) {
    if (this == &o)return *this;
    delete[] num;
    str = o.str;
    len = o.len;
    positive = o.positive;
    num = new int[len];
    for (int i = 0; i < len; i++)num[i] = o.num[i];
    return *this;
}

ArbitraryPrecisionInt &ArbitraryPrecisionInt::operator=(ArbitraryPrecisionInt &&o) {
    str = o.str;
    len = o.len;
    positive = o.positive;
    num = o.num;
    o.num = nullptr;
}

ArbitraryPrecisionInt::~ArbitraryPrecisionInt() {
    delete[] num;
}

ArbitraryPrecisionInt ArbitraryPrecisionInt::operator-() {
    if (*this == ArbitraryPrecisionIntZero)return *this;
    positive = (!positive);
    return *this;
}

ArbitraryPrecisionInt &ArbitraryPrecisionInt::operator+=(const ArbitraryPrecisionInt &o) {
    *this = (*this + o);
    return *this;
}

ArbitraryPrecisionInt &ArbitraryPrecisionInt::operator-=(const ArbitraryPrecisionInt &o) {
    *this = (*this - o);
    return *this;
}

ArbitraryPrecisionInt &ArbitraryPrecisionInt::operator*=(const ArbitraryPrecisionInt &o) {
    *this = (*this * o);
    return *this;
}

ArbitraryPrecisionInt &ArbitraryPrecisionInt::operator/=(const ArbitraryPrecisionInt &o) {
    *this = (*this / o);
    return *this;
}

ArbitraryPrecisionInt &ArbitraryPrecisionInt::operator%=(const ArbitraryPrecisionInt &o) {
    *this = (*this % o);
    return *this;
}

ArbitraryPrecisionInt &ArbitraryPrecisionInt::operator++() {
    *this += ArbitraryPrecisionIntOne;
    return *this;
}

ArbitraryPrecisionInt ArbitraryPrecisionInt::operator++(int) {
    ArbitraryPrecisionInt temp = *this;
    *this += ArbitraryPrecisionIntOne;
    return temp;
}

ArbitraryPrecisionInt &ArbitraryPrecisionInt::operator--() {
    *this -= ArbitraryPrecisionIntOne;
    return *this;
}

ArbitraryPrecisionInt ArbitraryPrecisionInt::operator--(int) {
    ArbitraryPrecisionInt temp = *this;
    *this -= ArbitraryPrecisionIntOne;
    return temp;
}

ArbitraryPrecisionInt ArbitraryPrecisionInt::pow(int power) {
    ArbitraryPrecisionInt temp(*this);
    for (int i = 0; i < power; i++) {
        (*this) *= temp;
    }
    return *this;
}

ArbitraryPrecisionInt ArbitraryPrecisionInt::multiple_ten(int bit) {
    if ((len == 1) && (num[0] == 0))return *this;
    if (bit == 0)return *this;
    ArbitraryPrecisionInt &o = *this;
    int *tempo = new int[o.len + bit];
    for (int i = 0; i < o.len + bit; i++) {
        tempo[i] = (i < bit ? 0 : o.num[i - bit]);
    }
    ArbitraryPrecisionInt temp(tempo, o.len + bit, o.positive);
    delete[] tempo;
    *this = temp;
    return *this;
}

ArbitraryPrecisionInt ArbitraryPrecisionInt::devide_ten(int bit) {
    if ((len == 1) && (num[0] == 0))return *this;
    ArbitraryPrecisionInt temp(num + bit, len - bit, positive);
    *this = temp;
    return *this;
}

istream &operator>>(istream &is, ArbitraryPrecisionInt &o) {
    delete[] o.num;
    is >> o.str;
    o.positive = true;
    if (o.str[0] == '-') {
        o.positive = false;
        (o.str).erase(0, 1);
    }
    o.len = (o.str).length();
    o.num = new int[o.len];
    for (int i = 0; i < o.len; i++) {
        o.num[i] = o.str[o.len - i - 1] - '0';
    }
    return is;
}

ostream &operator<<(ostream &os, const ArbitraryPrecisionInt &o) {
    if (!o.positive)os << "-";
    os << o.str;
    return os;
}

bool operator==(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2) {
    if (o1.len == o2.len && o1.positive == o2.positive && o1.str == o2.str)return true;
    else return false;
}

bool operator!=(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2) {
    return !(o1 == o2);
}

bool operator<(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2) {
    if ((!o1.positive) && o2.positive)return true;
    else if (o1.positive && (!o2.positive))return false;
    else if (o1.positive) {
        if (o1.len < o2.len)return true;
        else if (o1.len > o2.len)return false;
        else {
            for (int i = 0; i < o1.len; i++) {
                if (o1.str[i] < o2.str[i])return true;
                else if (o1.str[i] > o2.str[i])return false;
            }
            //o1==o2
            return false;
        }
    }
    else {
        return (-o2) < (-o1);
    }
}

bool operator>(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2) {
    if (o1 == o2)return false;
    else return (o2 < o1);
}

bool operator<=(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2) {
    return !(o1 > o2);
}

bool operator>=(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2) {
    return !(o1 < o2);
}

ArbitraryPrecisionInt operator-(const ArbitraryPrecisionInt &o) {
    ArbitraryPrecisionInt temp(o);
    return -temp;
}

ArbitraryPrecisionInt abs(const ArbitraryPrecisionInt &o) {
    if (o >= ArbitraryPrecisionInt(0))return o;
    else return -o;
}

ArbitraryPrecisionInt operator+(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2) {
    if (o1.positive == o2.positive) {
        int mino = (o1.len < o2.len ? 1 : 2);
        int maxo = 3 - mino;
        int size[3] = {0, o1.len, o2.len};
        int *o = new int[size[maxo] + 1];
        for (int i = 0; i <= size[maxo]; i++)o[i] = 0;
        for (int i = 0; i < size[mino]; i++) {
            o[i] += (o1.num[i] + o2.num[i]);
            if (o[i] >= 10) {
                o[i] -= 10;
                o[i + 1]++;
            }
        }
        for (int i = size[mino]; i < size[maxo]; i++) {
            o[i] += (maxo == 1 ? o1.num[i] : o2.num[i]);
            if (o[i] >= 10) {
                o[i] -= 10;
                o[i + 1]++;
            }
        }
        ArbitraryPrecisionInt temp(o, (o[size[maxo]] == 0 ? size[maxo] : size[maxo] + 1), o1.positive);
        delete[] o;
        return temp;
    }
    else {
        //to find out answer pos or neg
        bool ans_pos;
        if (o1 == (-o2))return ArbitraryPrecisionInt(0);
        if (o1.positive) {
            if (o1 > (-o2))ans_pos = true;
            else ans_pos = false;
        }
        else {
            if (o1 > (-o2))ans_pos = false;
            else ans_pos = true;
        }
        
        //calculate
        ArbitraryPrecisionInt zero(0);
        ArbitraryPrecisionInt abs1 = (o1 >= zero ? o1 : -o1), abs2 = (o2 >= zero ? o2 : -o2);
        ArbitraryPrecisionInt big = (abs1 >= abs2 ? abs1 : abs2), small = (abs1 >= abs2 ? abs2 : abs1);
        for (int i = 0; i < small.len; i++) {
            if (big.num[i] < small.num[i]) {
                big.num[i + 1]--;
                big.num[i] += 10;
            }
            big.num[i] -= small.num[i];
        }
        for (int i = small.len; i < big.len; i++) {
            if (big.num[i] < 0) {
                big.num[i] += 10;
                big.num[i + 1]--;
            }
        }
        int cnt = 0;
        for (int i = big.len - 1; i >= 0; i--) {
            if (big.num[i] == 0)cnt++;
            else break;
        }
        return ArbitraryPrecisionInt(big.num, big.len - cnt, ans_pos);
    }
}

ArbitraryPrecisionInt operator-(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2) {
    return (o1 + (-o2));
}

ArbitraryPrecisionInt operator*(const ArbitraryPrecisionInt &o, int o_) {
    if (o_ == 0)return ArbitraryPrecisionInt(0);
    if (o_ > 0 && o_ < 10) {
        int *tempo = new int[o.len + 1];
        for (int i = 0; i <= o.len; i++)tempo[i] = 0;
        for (int i = 0; i < o.len; i++) {
            tempo[i] += o.num[i] * o_;
            if (tempo[i] >= 10) {
                tempo[i + 1] += (tempo[i] / 10);
                tempo[i] %= 10;
            }
        }
        ArbitraryPrecisionInt temp(tempo, (tempo[o.len] > 0 ? o.len + 1 : o.len), (o_ > 0 ? (o.positive ? 1 : 0) : (o.positive ? 0 : 1)));
        delete[]tempo;
        return temp;
    }
    else {
        ArbitraryPrecisionInt oo(o_);
        return o * oo;
    }
}//multiple one digit int

ArbitraryPrecisionInt operator*(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2) {
    ArbitraryPrecisionInt result(0);
    if (o1 == result || o2 == result)return result;
    ArbitraryPrecisionInt tempabs = abs(o1);
    for (int i = 0; i < o2.len; i++) {
        ArbitraryPrecisionInt temp(tempabs * o2.num[i]);
        temp.multiple_ten(i);
        result += temp;
    }
    if (o1.positive != o2.positive)result = -result;
    return result;
}

ArbitraryPrecisionInt operator/(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2) {
    if (o2 == ArbitraryPrecisionIntZero)throw DevidedByZero();
    if (o1 == ArbitraryPrecisionIntZero)return o1;
    ArbitraryPrecisionInt t1 = abs(o1), t2 = abs(o2);
    if (t1 < t2) {
        if (o1.positive == o2.positive)return ArbitraryPrecisionInt(0);
        else return ArbitraryPrecisionInt(-1);
    }
    if (t1 == t2) {
        ArbitraryPrecisionInt result(1);
        if (o1.positive != o2.positive)result = -result;
        return result;
    }
    ArbitraryPrecisionInt result(0);
    for (int i = t1.len - t2.len; i >= 0; i--) {
        ArbitraryPrecisionInt temp = t2;
        temp.multiple_ten(i);
        ArbitraryPrecisionInt save = temp;
        int cnt = 0;
        for (int j = 1; j <= 12; j++) {
            if (temp > t1) {
                cnt = j - 1;
                temp -= save;
                break;
            }
            temp += save;
        }
        result.multiple_ten(1);
        if (cnt == 10)cnt = 9;
        result += (ArbitraryPrecisionInt) cnt;
        t1 -= temp;
    }
    if (o1.positive != o2.positive) {
        if (result * t2 != abs(o1))result++;
        result = -result;
    }
    return result;
}

ArbitraryPrecisionInt operator%(const ArbitraryPrecisionInt &o1, const ArbitraryPrecisionInt &o2) {
    return o1 - ((o1 / o2) * o2);
}

ArbitraryPrecisionInt::operator int() const {
    int result = 0;
    for (int i = len - 1; i >= 0; i--) {
        result *= 10;
        result += num[i];
    }
    return result;
}

ArbitraryPrecisionInt::operator double() const {
    double result = 0;
    for (int i = len - 1; i >= 0; i--) {
        result *= 10;
        result += num[i];
    }
    return result;
}

ArbitraryPrecisionInt::operator bool() const {
    if (*this == ArbitraryPrecisionIntZero)return false;
    else return true;
}

ArbitraryPrecisionInt::operator string() const {
    string result = (positive ? "" : "-");
    result += str;
    return result;
}

#pragma endregion

using namespace std;

int main() {
    ArbitraryPrecisionInt a, b;
    cin >> a >> b;
    cout << a + b << endl;
    return 0;
}