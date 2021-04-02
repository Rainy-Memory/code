//
// Created by Rainy Memory on 2021/3/30.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

template<class T>
inline void read(T &o) {
    char c = getchar();
    while (c < '0' || c > '9')c = getchar();
    o = 0;
    while (c >= '0' && c <= '9')o = (o << 3) + (o << 1) + c - '0', c = getchar();
}

template<class T>
class SegmentTree {
private:
    T *tree;
    T *add_tag;
    int size;
    
    void push_up(int p) {
        tree[p] = tree[p << 1] + tree[p << 1 | 1];
    }
    
    void push_down(int p, int s, int t) {
        int m = (s + t) >> 1;
        tree[p << 1] += add_tag[p] * (m - s + 1);
        tree[p << 1 | 1] += add_tag[p] * (t - m);
        add_tag[p << 1] += add_tag[p];
        add_tag[p << 1 | 1] += add_tag[p];
        add_tag[p] = 0;
    }
    
    void inner_build(T *a, int s, int t, int p) {
        add_tag[p] = 0;
        if (s == t) {
            tree[p] = a[s];
            return;
        }
        int m = (s + t) >> 1;
        inner_build(a, s, m, p << 1);
        inner_build(a, m + 1, t, p << 1 | 1);
        push_up(p);
    }
    
    void inner_add(int l, int r, int s, int t, int p, T delta) {
        if (l <= s && t <= r) {
            tree[p] += (t - s + 1) * delta;
            add_tag[p] += delta;
            return;
        }
        if (add_tag[p] != 0 && s < t)push_down(p, s, t);
        int m = (s + t) >> 1;
        if (l <= m)inner_add(l, r, s, m, p << 1, delta);
        if (m < r)inner_add(l, r, m + 1, t, p << 1 | 1, delta);
        push_up(p);
    }
    
    T inner_query(int l, int r, int s, int t, int p) {
        if (l <= s && t <= r)return tree[p];
        if (add_tag[p] != 0 && s < t)push_down(p, s, t);
        int m = (s + t) >> 1;
        T ret(0);
        if (l <= m)ret += inner_query(l, r, s, m, p << 1);
        if (m < r)ret += inner_query(l, r, m + 1, t, p << 1 | 1);
        return ret;
    }

public:
    SegmentTree(T *a, int n) : size(n) {
        tree = new T[size << 2];
        add_tag = new T[size << 2];
        inner_build(a, 1, size, 1);
    }
    
    ~SegmentTree() {
        delete[]tree;
        delete[]add_tag;
    }
    
    void rangeAdd(int l, int r, T delta) {
        inner_add(l, r, 1, size, 1, delta);
    }
    
    T querySum(int l, int r) {
        return inner_query(l, r, 1, size, 1);
    }
};

int n, m, x, y, op;
long long a[100007], d;

int main() {
    read(n), read(m);
    for (int i = 1; i <= n; i++)read(a[i]);
    SegmentTree<long long> st(a, n);
    for (int i = 0; i < m; i++) {
        read(op), read(x), read(y);
        if (op == 1) {
            read(d);
            st.rangeAdd(x, y, d);
        }
        else cout << st.querySum(x, y) << endl;
    }
    return 0;
}