//
// Created by Rainy Memory on 2020/12/29.
//

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double t;
    int n;
    cin >> t >> n;
    double ans1 = t / n;
    int ans2 = 2 * n;
    cout<<setiosflags(ios::fixed)<<setprecision(3);
    cout << ans1 << endl << ans2 << endl;
    return 0;
}