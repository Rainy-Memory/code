//
// Created by Rainy Memory on 2021/3/11.
//

#include <iostream>
#include <cstdio>

template<class T>
class SegmentTree {
private:
    T *tree;
    T *lazy;
    int size;
    
    void push_up(int p) {
        tree[p] = tree[p << 1] + tree[p << 1 | 1];
    }
    
    void inner_build(T *a, int s, int t, int p) {
        if (s == t) {
            T aa = a[s];
            tree[p] = a[s];
            return;
        }
        int m = (s + t) >> 1;
        inner_build(a, s, m, p << 1);
        inner_build(a, m + 1, t, p << 1 | 1);
        push_up(p);
    }
    
    void push_down(int p, int len) {
        tree[p << 1] += lazy[p] * (len - (len >> 1));
        tree[p << 1 | 1] += lazy[p] * (len >> 1);
        lazy[p << 1] += lazy[p];
        lazy[p << 1 | 1] += lazy[p];
        lazy[p] = 0;
    }
    
    void inner_single_update(int index, int delta, int s, int t, int p) {
        if (s == t) {
            tree[p] += delta;
            return;
        }
        int m = (s + t) >> 1;
        if (index <= m)inner_single_update(index, delta, s, m, p << 1);
        else inner_single_update(index, delta, m + 1, t, p << 1 | 1);
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
    
    T inner_sum(int l, int r, int s, int t, int p) {
        if (l <= s && t <= r)return tree[p];
        int m = (s + t) >> 1;
        if (lazy[p] != 0 && s < t)push_down(p, t - s + 1);
        T sum = 0;
        if (l <= m)sum += inner_sum(l, r, s, m, p << 1);
        if (m < r)sum += inner_sum(l, r, m + 1, t, p << 1 | 1);
        return sum;
    }

public:
    SegmentTree(T *a, int s) : size(s) {
        int len = size << 2;
        tree = new T[len];
        lazy = new T[len];
        for (int i = 0; i < len; i++)tree[i] = lazy[i] = 0;
        inner_build(a, 1, size, 1);
    }
    
    T rangeSum(int l, int r) {
        return inner_sum(l, r, 1, size, 1);
    }
    
    void update(int l, int r, T delta) {
        inner_update(l, r, delta, 1, size, 1);
    }
    
    void update(int index, T delta) {
        inner_single_update(index, delta, 1, size, 1);
    }
};

int n, m, op, x, y, k;
long long a[100005] = {0};

using namespace std;

int main() {
//    scanf("%d %d", &n, &m);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)cin >> a[i];//scanf("%d", &a[i]);
    SegmentTree<long long> st(a, n);
    for (int i = 0; i < m; i++) {
//        scanf("%d", &op);
        cin >> op;
        if (op == 1) {
//            scanf("%d %d %d", &x, &y, &k);
            cin >> x >> y >> k;
            st.update(x, y, k);
        }
        else {
//            scanf("%d %d", &x, &y);
            cin >> x >> y;
//            printf("%d\n", st.rangeSum(x, y));
            cout << st.rangeSum(x, y) << endl;
        }
    }
    return 0;
}