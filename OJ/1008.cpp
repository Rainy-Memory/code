//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
#include <stdio.h>
using namespace std;

int snowland[2000][2000] = { 0 }, sum[2000][2000] = { 0 };
int n, m, k;

bool judge(int size) {
    for (int i = 1; i <= n - size + 1; i++) {
        for (int j = 1; j <= m - size * 2 + 1; j++) {
            int num = sum[i + size - 1][j + 2 * size - 1] + sum[i - 1][j - 1] - sum[i + size - 1][j - 1] - sum[i - 1][j + 2 * size - 1];
            if (num == 0)return true;
        }
    }
    return false;
}

int main() {
    //initiate
    cin >> n >> m;
    if (m >= 2 * n)k = n;
    else k = m / 2;
    for (int i = 1; i <= n; i++) {
        char a[2000];
        cin >> a;
        for (int j = 1; j <= m; j++) {
            if (a[j - 1] == 'X')snowland[i][j] = 1;
            else snowland[i][j] = 0;
        }
    }
    
    //compute prefix
    sum[1][1] = snowland[1][1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i != 1) {
                sum[i][j + 1] = sum[i][j] + sum[i - 1][j + 1] - sum[i - 1][j] + snowland[i][j + 1];
            }
            if (i == 1) {
                sum[i][j + 1] = sum[i][j] + snowland[i][j + 1];
            }
        }
        sum[i + 1][1] = sum[i][1] + snowland[i + 1][1];
    }
    
    //binary search
    int min = 1, max = k, s = 0, SIZE = 0;
    while (s == 0) {
        int mid = (min + max) / 2;
        if (max - min >= 5) {
            if (judge(mid)) {
                min = mid;
            }
            else {
                max = mid;
            }
        }
        else {
            for (int i = max; i >= min; i--) {
                if (judge(i)) {
                    SIZE = i;
                    s++;
                    break;
                }
            }
        }
    }
    cout << SIZE * SIZE * 2 << endl;
    
    /*
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << sum[i][j] << " ";
        }
        cout << endl;
    }
    */
    
    return 0;
}