//
// Created by Rainy Memory on 2020/12/4.
//

#include<iostream>
using namespace std;
long long w0[21][21][21] = { 0 };
long long w(long long a, long long b, long long c) {
    if ((a <= 0) | (b <= 0) | (c <= 0)) {
        return 1;
    }
    else if ((a > 20) | (b > 20) | (c > 20)) {
        return w(20, 20, 20);
    }
    else if (a < b && b < c) {
        if (w0[a][b][c] != 0)return w0[a][b][c];
        else {
            int x = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
            w0[a][b][c] = x;
            return x;
        }
    }
    else {
        if (w0[a][b][c] != 0)return w0[a][b][c];
        else {
            int y = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
            w0[a][b][c] = y;
            return y;
        }
    }
}
int main() {
    int a0, b0, c0;
    while (cin >> a0 >> b0 >> c0) {
        cout << w(a0, b0, c0) << endl;
    }
    return 0;
}