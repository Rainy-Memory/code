//
// Created by Rainy Memory on 2021/4/9.
//

#include <iostream>
#include <cstring>

using namespace std;

#define maxn 1000007

char s1[maxn], s2[maxn];
int border[maxn], j = 0, l1, l2;

int main() {
    ios::sync_with_stdio(false);
    cin >> (s1 + 1) >> (s2 + 1);
    l1 = strlen(s1 + 1), l2 = strlen(s2 + 1);
    border[1] = 0;
    for (int i = 2; i <= l2; i++) {
        while (j > 0 && s2[i] != s2[j + 1])j = border[j];
        if (s2[i] == s2[j + 1])j++;
        border[i] = j;
    }
    j = 0;
    for (int i = 1; i <= l1; i++) {
        while (j > 0 && s1[i] != s2[j + 1])j = border[j];
        if (s1[i] == s2[j + 1])j++;
        if (j == l2)cout << i - l2 + 1 << endl, j = border[j];
    }
    for (int i = 1; i <= l2; i++)cout << border[i] << " ";
    return 0;
}