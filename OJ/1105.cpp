//
// Created by Rainy Memory on 2021/3/18.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

inline void read(int &o) {
    o = 0;
    char c = getchar();
    while (c > '9' || c < '0')c = getchar();
    while (c <= '9' && c >= '0')o = (o << 3) + (o << 1) + c - '0', c = getchar();
}

int n, top, res = -1;
int sequence[505];
int rearrange[505][505];
int dp[505];

int main() {
    read(n);
    for (int i = 0; i < n; i++) {
        read(sequence[i]);
        for (int j = 0; j < n; j++) {
            rearrange[j][(i + j) % n] = sequence[i];
        }
    }
    for (int now = 0; now < n; now++) {
        std::memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (int i = 1; i < n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (rearrange[now][i] > rearrange[now][j]) {
                    if (dp[i] < dp[j] + 1)dp[i] = dp[j] + 1;
                }
            }
        }
        int max = -1;
        for (int i = 0; i < n; i++) {
            if (max < dp[i])max = dp[i];
        }
        if (res < max)res = max;
    }
    cout << n - res << endl;
    return 0;
}