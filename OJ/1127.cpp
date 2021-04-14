//
// Created by Rainy Memory on 2021/4/11.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

template<class T>
inline void read(T &o) {
    char c = getchar();
    while (c < '0' || c > '9')c = getchar();
    o = 0;
    while (c >= '0' && c <= '9')o = (o << 3) + (o << 1) + c - '0', c = getchar();
}

#define maxn 600007
int n, m;
string str;
int trie[maxn][3] = {0}, cnt = 0, len = 0;
bool exist[maxn] = {false};

bool check(int now, int p, bool flag) {
    if (now == len) {
        if (flag && exist[p])return true;
        else return false;
    }
    if (trie[p][str[now] - 'a'] != 0) {
        if (check(now + 1, trie[p][str[now] - 'a'], flag))return true;
    }
    if (flag)return false;
    for (int i = 0; i < 3; i++) {
        if (i != str[now] - 'a' && trie[p][i] != 0) {
            if (check(now + 1, trie[p][i], true))return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int l, p;
    while (n--) {
        cin >> str;
        l = str.length(), p = 0;
        for (int i = 0; i < l; i++) {
            if (trie[p][str[i] - 'a'] == 0)trie[p][str[i] - 'a'] = ++cnt;
            p = trie[p][str[i] - 'a'];
        }
        exist[p] = true;
    }
    while (m--) {
        cin >> str;
        len = str.length();
        if (check(0, 0, false))cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}