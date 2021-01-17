//
// Created by Rainy Memory on 2021/1/9.
//
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

class test {
private:
    int data;

public:
    test() {
        cout << "constructor test()" << endl;
    }
    
    test(int o) : data(o) {
        cout << "constructor test(int o)" << endl;
    }
    
    ~test() {
        cout << "destructor ~test()" << endl;
    }
    
    void display() const {
        cout << data << endl;
    }
};

void testfunc(const test &o = 0) {
    o.display();
}

int main() {
    time_t now = time(0);
    string str = ctime(&now);
    char temp[40]={'s','a'};
    //strcpy(temp, str.c_str());
    cout << temp;
    return 0;
}