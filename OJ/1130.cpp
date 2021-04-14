//
// Created by Rainy Memory on 2021/4/12.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

#define maxk 3000007
int k, m, ptr1 = 0, ptr2 = 0, cnt = 0, r1, r2, top = 0, now;
int set[maxk];
int after[maxk];
string before;

int main() {
    ios::sync_with_stdio(false);
    cin >> k >> m;
    set[cnt++] = 1;
    while (cnt < k) {
        r1 = set[ptr1] * 2 + 1, r2 = set[ptr2] * 4 + 5;
        if (r1 < r2)set[cnt++] = r1, ptr1++;
        else set[cnt++] = r2, ptr2++;
    }
    for (int i = 0; i < k; i++)before += to_string(set[i]);
    cout << before << endl;
    for (char i : before) {
        now = i - '0';
        while (top > 0 && m > 0 && now > after[top - 1])top--, m--;
        after[top++] = now;
    }
    top -= m;
    for (int i = 0; i < top; i++)cout << after[i];
    cout << endl;
    return 0;
}