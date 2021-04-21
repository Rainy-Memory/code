//
// Created by RainyMemory on 2021/4/15.
//

#include <iostream>
#include <cstring>

using namespace std;

#define maxn 30
int n1, n2;
int l1[maxn] = {0}, r1[maxn] = {0};
int l2[maxn] = {0}, r2[maxn] = {0};
char info1[maxn] = {'\0'}, info2[maxn] = {'\0'};
bool exist1[maxn] = {false}, exist2[maxn] = {false};
bool notroot1[maxn] = {false}, notroot2[maxn] = {false};
int map1[maxn] = {0}, map2[maxn] = {0};
char c;
string lc_str[maxn], rc_str[maxn];

int my_to_int(const string &o) {
    int ret = 0;
    for (int i = 0; i < o.length(); i++) {
        ret = ret * 10 + o[i] - '0';
    }
    return ret;
}

void read() {
    cin >> n1;
    for (int i = 0; i < n1; i++) {
        cin >> c >> lc_str[i] >> rc_str[i];
        exist1[c - 'A'] = true;
        info1[i] = c;
        map1[c - 'A'] = i;
    }
    for (int i = 0; i < n1; i++) {
        int lc = my_to_int(lc_str[i]), rc = my_to_int(rc_str[i]);
        if (lc_str[i] != "-") {
            if (rc_str[i] != "-") {
                int min = info1[lc] < info1[rc] ? lc : rc, max = info1[lc] < info1[rc] ? rc : lc;
                l1[i] = min, r1[i] = max;
                notroot1[lc] = notroot1[rc] = true;
            }
            else {//rc == '-'
                l1[i] = lc;
                notroot1[lc] = true;
            }
        }
        else {//lc == '-'
            if (rc_str[i] != "-") {
                l1[i] = rc;
                notroot1[rc] = true;
            }
        }
    }
    cin >> n2;
    for (int i = 0; i < n2; i++) {
        cin >> c >> lc_str[i] >> rc_str[i];
        exist2[c - 'A'] = true;
        info2[i] = c;
        map2[c - 'A'] = i;
    }
    for (int i = 0; i < n2; i++) {
        int lc = my_to_int(lc_str[i]), rc = my_to_int(rc_str[i]);
        if (lc_str[i] != "-") {
            if (rc_str[i] != "-") {
                int min = info2[lc] < info2[rc] ? lc : rc, max = info2[lc] < info2[rc] ? rc : lc;
                l2[i] = min, r2[i] = max;
                notroot2[lc] = notroot2[rc] = true;
            }
            else {//rc == '-'
                l2[i] = lc;
                notroot2[lc] = true;
            }
        }
        else {//lc == '-'
            if (rc_str[i] != "-") {
                l2[i] = rc;
                notroot2[rc] = true;
            }
        }
    }
}

bool dfs(int now1, int now2) {
    if (now1 == -1 || now2 == -1) {
        return now1 == now2;
    }
    if (info1[now1] != info2[now2])return false;
    return dfs(l1[now1], l2[now2]) && dfs(r1[now1], r2[now2]);
}

bool check() {
    if (n1 != n2)return false;
    for (int i = 0; i < maxn; i++) {
        if (exist1[i] != exist2[i])return false;
    }
    char first1, first2;
    for (int i = 0; i < n1; i++) {
        if (!notroot1[i] && exist1[info1[i] - 'A']) {
            first1 = info1[i];
            break;
        }
    }
    for (int i = 0; i < n2; i++) {
        if (!notroot2[i] && exist2[info2[i] - 'A']) {
            first2 = info2[i];
            break;
        }
    }
    int start1 = map1[first1 - 'A'], start2 = map2[first2 - 'A'];
    return dfs(start1, start2);
}

int main() {
    ios::sync_with_stdio(false);
    memset(l1, -1, sizeof(l1));
    memset(l2, -1, sizeof(l2));
    memset(r1, -1, sizeof(r1));
    memset(r2, -1, sizeof(r2));
    read();
    if (check())cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}