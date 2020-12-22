//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
using namespace std;
long long s[20000000] = { 0 };
int main() {
    long long n, t, k, count = 0;
    cin >> n >> t >> k;
    for (long long i = 0; i < n; i++) {
        long long sleep;
        cin >> sleep;
        s[sleep]++;
    }
    
    long long finish = 0, a = 0;
    for (long long i = 19999999; i >= 0; i--) {
        if (s[i] != 0) {
            a = i;
            break;
        }
    }
    //最大瞌睡值为a;
    for (long long i = 0; i <= a; i++) {
        if (s[i] != 0) {
            for (long long j = 0; j < s[i]; j++) {
                if (t + i >= k)break;
                else {
                    while (s[i] != 0) {
                        t += i;
                        finish++;
                        s[i]--;
                        if (t + i >= k)break;
                    }
                }
                
            }
        }
    }
    long long x = 0;
    double score;
    score = 10 + 90 * finish / n;
    for (int i = 0; i <= 100; i++) {
        if (i <= score && score < i + 1)x = i;
    }
    cout << x << endl;
    return 0;
}