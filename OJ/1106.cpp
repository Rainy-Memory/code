//
// Created by Rainy Memory on 2021/3/18.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

#define maxn 4005

template<class T>
class SegmentTree {
private:
    T *tree;
    T *lazy;
    int size;
    
    T max(const T &o1, const T &o2) {
        return o1 > o2 ? o1 : o2;
    }
    
    void push_up(int p) {
        tree[p] = max(tree[p << 1], tree[p << 1 | 1]);
    }
    
    void push_down(int p, int len) {
        tree[p << 1] += lazy[p] * (len - (len >> 1));
        tree[p << 1 | 1] += lazy[p] * (len >> 1);
        lazy[p << 1] += lazy[p];
        lazy[p << 1 | 1] += lazy[p];
        lazy[p] = 0;
    }
    
    void inner_build(T *a, int s, int t, int p) {
        if (s == t) {
            tree[p] = a[s];
            return;
        }
        int m = (s + t) >> 1;
        inner_build(a, s, m, p << 1);
        inner_build(a, m + 1, t, p << 1 | 1);
        push_up(p);
    }
    
    void inner_update(int l, int r, int delta, int s, int t, int p) {
        if (l <= s && t <= r) {
            tree[p] += (t - s + 1) * delta;
            if (s != t)lazy[p] += delta;
            return;
        }
        int m = (s + t) >> 1;
        if (lazy[p] != 0 && s < t)push_down(p, t - s + 1);
        if (l <= m)inner_update(l, r, delta, s, m, p << 1);
        if (m < r)inner_update(l, r, delta, m + 1, t, p << 1 | 1);
        push_up(p);
    }
    
    T inner_max(int l, int r, int s, int t, int p) {
        if (l <= s && t <= r)return tree[p];
        if (lazy[p] != 0 && s < t)push_down(p, t - s + 1);
        int m = (s + t) >> 1;
        T ret = -1;
        int temp;
        if (l <= m) {
            temp = inner_max(l, r, s, m, p << 1);
            ret = ret == -1 ? temp : max(ret, temp);
        }
        if (m < r) {
            temp = inner_max(l, r, m + 1, t, p << 1 | 1);
            ret = ret == -1 ? temp : max(ret, temp);
        }
        return ret;
    }

public:
    SegmentTree(T *a, int s) : size(s) {
        int len = size << 2;
        tree = new T[len];
        lazy = new T[len];
        for (int i = 0; i < len; i++)tree[i] = lazy[i] = 0;
        inner_build(a, 1, size, 1);
    }
    
    ~SegmentTree() {
        delete[]tree;
    }
    
    void update(int l, int r, T delta) {
        inner_update(l, r, delta, 1, size, 1);
    }
    
    T rangeMax(int l, int r) {
        return inner_max(l, r, 1, size, 1);
    }
};

inline void read(int &o) {
    o = 0;
    char c = getchar();
    while (c > '9' || c < '0')c = getchar();
    while (c <= '9' && c >= '0')o = (o << 3) + (o << 1) + c - '0', c = getchar();
}

int n, top = 0, res = -1;
int sequence[maxn];
int v[maxn];
int MonotoneStack[maxn];

void solveSegmentTree() {
    read(n);
    for (int i = 0; i < n; i++) {
        read(sequence[i]);
        sequence[i + n] = sequence[i];
    }
    for (int now = 0; now < n; now++) {
        memset(v, 0, sizeof(v));
        SegmentTree<int> st(v, maxn);
        for (int i = 0; i < n; i++) {
            int seqmax = (sequence + now)[i] > 1 ? st.rangeMax(1, (sequence + now)[i] - 1) : 0;
            v[(sequence + now)[i]] = seqmax + 1;
            st.update((sequence + now)[i], (sequence + now)[i], seqmax + 1);
        }
        int maxseq = st.rangeMax(1, n);
        if (res < maxseq)res = maxseq;
    }
    cout << n - res << endl;
}

namespace rm {
    template<class ptr, class T>
    ptr lower_bound(ptr first, ptr last, const T &val) {
        ptr now;
        int count = last - first, step;
        while (count > 0) {
            step = count >> 1;
            now = first + step;
            if (*now < val) {
                first = ++now;
                count -= step + 1;
            }
            else count = step;
        }
        return first;
    }
}

void solveMonotoneStack() {
    read(n);
    for (int i = 0; i < n; i++)read(sequence[i]), sequence[i + n] = sequence[i];
    for (int now = 0; now < n; now++, top = 0) {
        for (int i = now; i < n + now; i++) {
            if (sequence[i] > MonotoneStack[top - 1])MonotoneStack[top++] = sequence[i];
            else MonotoneStack[rm::lower_bound(MonotoneStack, MonotoneStack + top, sequence[i]) - MonotoneStack] = sequence[i];
        }
        if (res < top)res = top;
    }
    cout << n - res << endl;
}

int main() {
//    solveSegmentTree();
    solveMonotoneStack();
    return 0;
}