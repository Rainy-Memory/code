//
// Created by Rainy Memory on 2021/4/2.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

int n;
char fbi[4100];
char tree[4100] = {'\0'};
bool have_value[4100] = {false};

void build(int s, int t, int p) {
    have_value[p] = true;
    if (s == t) {
        tree[p] = fbi[s - 1] == '0' ? 'B' : 'I';
        return;
    }
    int m = (s + t) >> 1;
    build(s, m, p << 1);
    build(m + 1, t, p << 1 | 1);
    if (tree[p << 1] == 'B' && tree[p << 1 | 1] == 'B')tree[p] = 'B';
    else if (tree[p << 1] == 'I' && tree[p << 1 | 1] == 'I')tree[p] = 'I';
    else tree[p] = 'F';
}

void post_order_traversal(int p) {
    if (!have_value[p])return;
    post_order_traversal(p << 1);
    post_order_traversal(p << 1 | 1);
    cout << tree[p];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> fbi;
    build(1, 1 << n, 1);
    post_order_traversal(1);
    return 0;
}