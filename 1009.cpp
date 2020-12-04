//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
using namespace std;
int a[200000] = { 0 }, b[200000] = { 0 };
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < m; i++) {
        int x = b[i], s = 0, min = 0, max = n - 1;
        if (x > a[n - 1])cout << "-1" << endl;
        else {
            while (s == 0) {
                int cor = (min + max) / 2;
                if (max - min >= 5) {
                    if (a[cor] >= x)max = cor;
                    else min = cor;
                }
                else {
                    for (int j = min; j <= max; j++) {
                        if (a[j] >= x) {
                            cout << a[j] << endl;
                            s++;
                            break;
                        }
                    }
                }
            }
        }
        
        
    }
    return 0;
}