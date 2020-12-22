//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
using namespace std;
int a[200000] = { 0 }, c[200000] = { 0 }, sum[200000] = { 0 };
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sum[1] = a[1];
    for (int i = 2; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> c[i];
    }
    for (int i = 1; i <= m; i++) {
        int no = c[i], shaft = 0, position = 0, s = 0, max = n, min = 1;
        while (s == 0) {
            int mid = (max + min) / 2;
            if (max - min >= 5) {
                if (sum[mid] > no)max = mid;
                else min = mid;
            }
            else {
                for (int j = min; j <= max; j++) {
                    if (sum[j] >= no) {
                        shaft = j;
                        position = no - sum[j - 1];
                        s++;
                        break;
                    }
                }
            }
        }
        cout << shaft << " " << position << endl;
    }
    
    return 0;
}