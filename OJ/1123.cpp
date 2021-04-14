//
// Created by Rainy Memory on 2021/4/14.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

#define maxn 1<<7
int n;
int map[7][maxn];
int ability[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < (1 << n); i++) {
        cin >> ability[i];
        map[0][i] = i;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < (1 << (n - i + 1)); j += 2) {
            map[i][j >> 1] = ability[map[i - 1][j]] > ability[map[i - 1][j + 1]] ? map[i - 1][j] : map[i - 1][j + 1];
        }
    }
    cout << (ability[map[n - 1][0]] > ability[map[n - 1][1]] ? map[n - 1][1] : map[n - 1][0]) + 1 << endl;
    return 0;
}