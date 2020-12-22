//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
using namespace std;
char room[200000] = { 0 };
int sumempty[200000] = { 0 };
int n, k;
int empty(int x, int y) {
    int emptyroom;
    if (x != 0)emptyroom = sumempty[y] - sumempty[x - 1];
    else {
        emptyroom = sumempty[y];
    }
    return emptyroom;
}
bool judge(int length) {
    if (room[0] == '0') {
        if (empty(1, length) >= k)return true;
    }
    for (int i = 1; i < length; i++) {
        if (room[i] != '1') {
            if (empty(0, i - 1) + empty(i + 1, i + length) >= k)return true;
        }
    }
    for (int i = length; i <= n - length - 1; i++) {
        if (room[i] != '1') {
            if (empty(i - length, i - 1) + empty(i + 1, i + length) >= k)return true;
        }
    }
    for (int i = n - length; i < n; i++) {
        if (room[i] != '1') {
            if (empty(i - length, i - 1) + empty(i + 1, n - 1) >= k)return true;
        }
    }
    if (room[n - 1] == '0') {
        if (empty(n - length - 1, n - 2) >= k)return true;
    }
    return false;
}
int main() {
    int result = 0;
    cin >> n >> k;
    cin >> room;
    sumempty[0] = ((room[0] == '0') ? 1 : 0);
    for (int i = 1; i < n; i++) {
        sumempty[i] = sumempty[i - 1] + ((room[i] == '0') ? 1 : 0);
    }
    int max = n, min = 1, s = 0;
    while (s == 0) {
        int mid = (max + min) / 2;
        if (max - min >= 5) {
            if (judge(mid)) max = mid;
            else min = mid;
        }
        else {
            for (int i = min; i <= max; i++) {
                if (judge(i)) {
                    result = i;
                    s++;
                    break;
                }
            }
        }
    }
    cout << result << endl;
    return 0;
}