//
// Created by Rainy Memory on 2021/4/12.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

#define maxn 30007
int n, cnt = 0;
int fa[maxn], l[maxn], r[maxn], w[maxn];

struct node {
    int self;
    int fa;
    int l;
    int r;
    int w;
    
    node(int _self, int _fa, int _l, int _r, int _w) : self(_self), fa(_fa), l(_l), r(_r), w(_w) {}
    
    node() = default;
    
    bool operator<(node o) const {
        return w > o.w;
    }
} t1, t2, t;

long long dfs(int now, int now_len) {
    if (l[now] == -1 && r[now] == -1)return w[now] * now_len;
    long long ret = 0;
    if (l[now] != -1)ret += dfs(l[now], now_len + 1);
    if (r[now] != -1)ret += dfs(r[now], now_len + 1);
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    memset(fa, -1, sizeof(fa));
    memset(l, -1, sizeof(l));
    memset(r, -1, sizeof(r));
    priority_queue<node> heap;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        heap.push(node(i, -1, -1, -1, w[i]));
    }
    cnt = n;
    for (int i = 0; i < n - 1; i++) {
        t1 = heap.top(), heap.pop();
        t2 = heap.top(), heap.pop();
        l[cnt] = t.l = t1.self, r[cnt] = t.r = t2.self, t.fa = -1, t.self = cnt, w[cnt] = t.w = t1.w + t2.w;
        fa[t1.self] = fa[t2.self] = cnt++;
        heap.push(t);
    }
    t = heap.top();
    cout << dfs(t.self, 0) << endl;
    return 0;
}