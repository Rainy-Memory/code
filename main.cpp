//
// Created by Rainy Memory on 2021/1/9.
//
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <map>
#include <ctime>

using namespace std;

int main() {
    map<int, int> m;
    m[0] = 0;
    m[1] = 1;
    cout << (--m.begin())->first << endl;
    cout << (++m.end())->first << endl;
    return 0;
}