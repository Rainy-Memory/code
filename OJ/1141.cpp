//
// Created by Rainy Memory on 2021/4/2.
//

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
typedef unsigned long long ull;

#define PRIME 1000000007

ull getHash1(const string &o) {
    ull h = o.length();
    for (int i = 0; i < o.size(); i++)h = (h << 4) ^ (h >> 28) ^ o[i];
    return h % PRIME;
}

ull getHash2(const string &o) {
    ull h = o.length();
    for (int i = 0; i < o.size(); i++)h = (h << 7) ^ (h >> 25) ^ o[i];
    return h % PRIME;
}

ull str_hash(const string &o) {
    return ull(getHash1(o) << 32 | getHash2(o));
}

int n, cnt = 1;
string s;
ull a[10007];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s;
        a[i] = str_hash(s);
    }
    sort(a, a + n);
    for (int i = 0; i < n - 1; i++) {
        if (a[i] != a[i + 1])cnt++;
    }
    cout << cnt << endl;
    return 0;
}