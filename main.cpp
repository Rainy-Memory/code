//
// Created by Rainy Memory on 2021/1/9.
//

#include <iostream>
#include <chrono>

using namespace std;

struct train_time_t {
    int month = 6;
    int day = 1;
    int hour = 0;
    int minute = 0;
    
    explicit train_time_t(int mo, int da, int ho = 0, int mi = 0) : month(mo), day(da), hour(ho), minute(mi) {}
    
    train_time_t() = default;
    
    friend std::ostream &operator<<(std::ostream &os, const train_time_t &t) {
        os << "0" << t.month << "-";
        if (t.day >= 10)os << t.day;
        else os << "0" << t.day;
        os << " ";
        if (t.hour >= 10)os << t.hour;
        else os << "0" << t.hour;
        os << ":";
        if (t.minute >= 10)os << t.minute;
        else os << "0" << t.minute;
        return os;
    }
    
    train_time_t operator+(int mi) {
        minute += mi;
        int ho = minute - minute % 60;
        minute %= 60;
        hour += ho / 60;
        int da = hour - hour % 24;
        hour %= 24;
        day += da / 24;
        if (month == 6 && day > 30)day -= 30, month++;
        if (month == 7 && day > 31)day -= 31, month++;
        if (month == 8 && day > 31)day -= 31, month++;
        return *this;
    }
    
    train_time_t &operator+=(int mi) {
        *this = *this + mi;
        return *this;
    }
    
    int operator-(const train_time_t &o) const {
        //return distance in minute
        if (*this > o)return dateDistance(o) * 24 * 60 + (hour - o.hour) * 60 + minute - o.minute;
        else return o.dateDistance(*this) * 24 * 60 + (o.hour - hour) * 60 + o.minute - minute;
    }
    
    int dateDistance(const train_time_t &o) const {
        if ((*this) <= o)return 0;
        //assume this is later than o
        int ret = day - o.day;
        switch (month - o.month) {
            case 3:
                ret += 92;
                break;
            case 2:
                ret += 61;
                break;
            case 1:
                if (month == 7)ret += 30;
                else ret += 31;
        }
        return ret;
    }
    
    train_time_t &updateDate(int da) {
        day += da;
        if (month == 6 && day > 30)day -= 30, month++;
        if (month == 7 && day > 31)day -= 31, month++;
        if (month == 8 && day > 31)day -= 31, month++;
        return *this;
    }
    
    bool operator<(const train_time_t &o) const {
        if (month < o.month)return true;
        else if (month > o.month)return false;
        if (day < o.day)return true;
        else if (day > o.day)return false;
        if (hour < o.hour)return true;
        else if (hour > o.hour)return false;
        if (minute < o.minute)return true;
        else return false;
    }
    
    bool operator==(const train_time_t &o) const {
        return month == o.month && day == o.day && hour == o.hour && minute == o.minute;
    }
    
    bool operator!=(const train_time_t &o) const {
        return !(*this == o);
    }
    
    bool operator>(const train_time_t &o) const {
        if (*this == o)return false;
        return !(*this < o);
    }
    
    bool operator<=(const train_time_t &o) const {
        if (*this == o)return true;
        return *this < o;
    }
    
    bool operator>=(const train_time_t &o) const {
        if (*this == o)return true;
        return !(*this < o);
    }
    
    bool lessOrEqualDate(const train_time_t &o) const {
        if (month < o.month)return true;
        else if (month > o.month)return false;
        if (day <= o.day)return true;
        else return false;
    }
};

int main() {

    return 0;
}