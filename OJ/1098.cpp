//
// Created by Rainy Memory on 2021/3/15.
//

#include <cstdio>
#include <iostream>

#define maxn 600000

int h[maxn] = {0};
int MonotoneStack[maxn] = {0};
int n, top = 0, result = -1;

template<class T>
class SegmentTree {
private:
    T *tree;
    int size;
    
    T min(const T &o1, const T &o2) {
        return h[o1] < h[o2] ? o1 : o2;
    }
    
    void push_up(int p) {
        tree[p] = min(tree[p << 1], tree[p << 1 | 1]);
    }
    
    void inner_build(T *a, int s, int t, int p) {
        if (s == t) {
            tree[p] = s;
            return;
        }
        int m = (s + t) >> 1;
        inner_build(a, s, m, p << 1);
        inner_build(a, m + 1, t, p << 1 | 1);
        push_up(p);
    }
    
    T inner_min(int l, int r, int s, int t, int p) {
        if (l <= s && t <= r)return tree[p];
        int m = (s + t) >> 1;
        T ret = -1;
        int temp;
        if (l <= m) {
            temp = inner_min(l, r, s, m, p << 1);
            ret = ret == -1 ? temp : min(ret, temp);
        }
        if (m < r) {
            temp = inner_min(l, r, m + 1, t, p << 1 | 1);
            ret = ret == -1 ? temp : min(ret, temp);
        }
        return ret;
    }

public:
    SegmentTree(T *a, int s) : size(s) {
        int len = size << 2;
        tree = new T[len];
        inner_build(a, 1, size, 1);
    }
    
    ~SegmentTree() {
        delete[]tree;
    }
    
    T rangeMin(int l, int r) {
        return inner_min(l, r, 1, size, 1);
    }
};

inline void read(int &o) {
    char c = getchar();
    while (c > '9' || c < '0')c = getchar();
    o = 0;
    while (c <= '9' && c >= '0')o = (o << 3) + (o << 1) + c - '0', c = getchar();
}

int main() {
    read(n);
    for (int i = 1; i <= n; i++)read(h[i]);
    SegmentTree<int> tree(h, n);
    for (int i = 1; i <= n; i++) {
        while (0 < top && h[MonotoneStack[top - 1]] <= h[i])top--;
        int res = tree.rangeMin(MonotoneStack[top - 1], i);
        if (result < i - res)result = i - res;
        MonotoneStack[top++] = i;
    }
    printf("%d\n", result + 1);
    return 0;
}