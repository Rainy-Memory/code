//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
using namespace std;
int main() {
    int n, s = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a > s)s = a;
    }
    cout << s << endl;
    return 0;
}