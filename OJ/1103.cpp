//
// Created by Rainy Memory on 2021/3/18.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

string element;

bool answer = false;
bool have_not = false;

int stack[1000000] = {0};//0: false, 1: true, 2: and, 3: or
int tail = 0;

bool solve() {
    while (cin >> element) {
        int len = element.length();
        if (len == 2) { //or
            if (have_not)return false;
            stack[tail++] = 3;
        }
        else if (len == 3) {
            if (element == "not") {
                have_not = !have_not;
            }
            else { //and
                if (have_not)return false;
                if (tail < 1 || stack[tail - 1] > 1)return false;
                stack[tail++] = 2;
            }
        }
        else if (len == 4) { //true
            if (have_not) {
                have_not = false;
                stack[tail++] = 0;
            }
            else stack[tail++] = 1;
            if (tail >= 2 && stack[tail - 2] == 2) {
                if (stack[tail - 3] > 1)return false;
                bool a1 = stack[tail - 3], a2 = stack[tail - 1];
                stack[tail - 3] = a1 && a2;
                tail -= 2;
            }
        }
        else if (len == 5) { //false
            if (have_not) {
                have_not = false;
                stack[tail++] = 1;
            }
            else stack[tail++] = 0;
            if (tail >= 2 && stack[tail - 2] == 2) {
                if (stack[tail - 3] > 1)return false;
                bool a1 = stack[tail - 3], a2 = stack[tail - 1];
                stack[tail - 3] = a1 && a2;
                tail -= 2;
            }
        }
    }
    if (tail % 2 == 0)return false;
    for (int i = 0; i < tail; i++) {
        if (i % 2 == 0) {
            if (stack[i] > 1)return false;
        }
        else {
            if (stack[i] != 3)return false;
        }
    }
    answer = stack[0] == 1;
    for (int i = 2; i < tail; i += 2) {
        answer = answer || stack[i];
    }
    return true;
}

int main() {
    if (solve())cout << (answer ? "true" : "false") << endl;
    else cout << "error" << endl;
    return 0;
}