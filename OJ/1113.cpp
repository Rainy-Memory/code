//
// Created by Rainy Memory on 2021/3/29.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

long long m, res = 1;
long long factorial[30];
char pre[30], post[30];

long long cmn(int n) {
    return factorial[m] / factorial[n] / factorial[m - n];
}

void calculate(int s1, int e1, int s2, int e2) {
    if (e1 - s1 == 1)return;
    s1++, e2--;
    int pos = 0, child_cnt = 0;
    while (s1 < e1) {
        for (int i = s2; i < e2; i++) {
            if (post[i] == pre[s1]) {
                pos = i;
                break;
            }
        }
        int new_s1 = s1, new_e1 = s1 + pos - s2 + 1, new_s2 = s2, new_e2 = pos + 1;
        s1 = new_e1, s2 = new_e2;
        child_cnt++;
        calculate(new_s1, new_e1, new_s2, new_e2);
    }
    res *= cmn(child_cnt);
}

int main() {
    scanf("%lld %s %s", &m, pre, post);
    factorial[0] = 1;
    for (int i = 1; i < 30; i++)factorial[i] = factorial[i - 1] * i;
    calculate(0, strlen(pre), 0, strlen(post));
    printf("%lld\n", res);
    return 0;
}