//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
#include <string.h>
using namespace std;

int r[1000010] = { 0 }, d[1000010] = { 0 }, s[1000010] = { 0 }, t[1000010] = { 0 }, sum[1000010] = { 0 }, mark[1000010] = { 0 };
int n, m;

bool judge(int a) {
    for (int j = 1; j <= a; j++) {
        mark[s[j]] += d[j];
        mark[t[j] + 1] -= d[j];
    }
    sum[1] = mark[1];
    for (int i = 2; i <= n; i++) {
        sum[i] = sum[i - 1] + mark[i];
    }
    for (int i = 1; i <= n; i++) {
        if (sum[i] > r[i]) {
            memset(sum, 0, sizeof(sum));
            memset(mark, 0, sizeof(mark));
            return false;
        }
    }
    memset(sum, 0, sizeof(sum));
    memset(mark, 0, sizeof(mark));
    return true;
}

int run() {
    int max = m, min = 1;
    while (true) {
        int mid = (max + min) / 2;
        if (max - min >= 5) {
            if (judge(mid))min = mid;
            else max = mid;
        }
        else {
            for (int i = min; i <= max; i++) {
                if (judge(i)) {
                    if (i == max)return 0;
                }
                else {
                    return i;
                }
            }
        }
    }
}

int main() {
    
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
    }
    for (int j = 1; j <= m; j++) {
        cin >> d[j] >> s[j] >> t[j];
    }
    
    int x = run();
    if (x == 0)cout << "0" << endl;
    else {
        cout << "-1" << endl;
        cout << x << endl;
    }
    return 0;
}