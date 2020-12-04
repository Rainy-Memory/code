//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
#include <string.h>
using namespace std;
int a[70000] = { 0 }, bn[200000] = { 0 };
int main() {
    int t;
    cin >> t;
    for (int i0 = 0; i0 < t; i0++) {
        memset(a, 0, sizeof(a));
        memset(bn, 0, sizeof(bn));
        int n;
        cin >> n;
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            int b, left = 65536, right = 65536, sl = 0, sr = 0;
            cin >> b;
            a[b]++;
            if (i == 0) {
                sum += b;
                continue;
            }
            if (a[b] >= 2) {
                bn[i] = 0;
            }
            else {
                for (int j = b - 1; j >= 0; j--) {
                    if (a[j] != 0) {
                        left = j;
                        sl++;
                        break;
                    }
                }
                for (int j = b + 1; j <= 65536; j++) {
                    if (a[j] != 0) {
                        right = j;
                        sr++;
                        break;
                    }
                }
                if (sl != 0 && sr != 0) {
                    int distance = (right - b > b - left ? b - left : right - b);
                    bn[i] = distance;
                }
                else if (sl != 0 && sr == 0) {
                    bn[i] = b - left;
                }
                else if (sl == 0 && sr != 0) {
                    bn[i] = right - b;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            sum += bn[i];
        }
        cout << sum << endl;
    }
    return 0;
}