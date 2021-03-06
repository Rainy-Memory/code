//
// Created by RainyMemory on 2021/4/1.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

#define maxn 100007

int N, M, op, x, y;
double arr[maxn], k;

template<class T>
class SegmentTree {
private:
    T *tree;
    T *power;
    T *add_tag;
    int size;
    
    void push_up(int p) {
        tree[p] = tree[p << 1] + tree[p << 1 | 1];
        power[p] = power[p << 1] + power[p << 1 | 1];
    }
    
    void push_down(int p, int s, int t) {
        int m = (s + t) >> 1;
        add_tag[p << 1] += add_tag[p];
        add_tag[p << 1 | 1] += add_tag[p];
        power[p << 1] += 2 * add_tag[p] * tree[p << 1] + (m - s + 1) * add_tag[p] * add_tag[p];
        power[p << 1 | 1] += 2 * add_tag[p] * tree[p << 1 | 1] + (t - m) * add_tag[p] * add_tag[p];
        tree[p << 1] += add_tag[p] * (m - s + 1);
        tree[p << 1 | 1] += add_tag[p] * (t - m);
        add_tag[p] = 0;
    }
    
    void inner_build(T *a, int s, int t, int p) {
        add_tag[p] = 0;
        if (s == t) {
            tree[p] = a[s];
            power[p] = a[s] * a[s];
            return;
        }
        int m = (s + t) >> 1;
        inner_build(a, s, m, p << 1);
        inner_build(a, m + 1, t, p << 1 | 1);
        push_up(p);
    }
    
    void inner_add(int l, int r, int s, int t, int p, T delta) {
        if (l <= s && t <= r) {
            power[p] += 2 * delta * tree[p] + (t - s + 1) * delta * delta;
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
    
    T inner_query(int l, int r, int s, int t, int p, bool query_power) {
        if (l <= s && t <= r) {
            if (query_power)return power[p];
            else return tree[p];
        }
        if (add_tag[p] != 0 && s < t)push_down(p, s, t);
        int m = (s + t) >> 1;
        T ret(0);
        if (l <= m)ret += inner_query(l, r, s, m, p << 1, query_power);
        if (m < r)ret += inner_query(l, r, m + 1, t, p << 1 | 1, query_power);
        return ret;
    }

public:
    SegmentTree(T *a, int s) : size(s) {
        tree = new T[size << 2];
        power = new T[size << 2];
        add_tag = new T[size << 2];
        inner_build(a, 1, size, 1);
    }
    
    ~SegmentTree() {
        delete[]tree;
        delete[]power;
        delete[]add_tag;
    }
    
    void rangeAdd(int l, int r, T delta) {
        inner_add(l, r, 1, size, 1, delta);
    }
    
    T querySum(int l, int r) {
        return inner_query(l, r, 1, size, 1, false);
    }
    
    T queryPowerSum(int l, int r) {
        return inner_query(l, r, 1, size, 1, true);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin >> N >> M;
    for (int i = 1; i <= N; i++)cin >> arr[i];
    SegmentTree<double> st(arr, N);
    for (int i = 0; i < M; i++) {
        cin >> op >> x >> y;
        if (op == 1) {
            cin >> k;
            st.rangeAdd(x, y, k);
        }
        else if (op == 2) {
            double res = st.querySum(x, y) / (y - x + 1);
            int r = int(res * 100);
            cout << r << "\n";
        }
        else {
            double avg = st.querySum(x, y) / (y - x + 1);
            double res1 = st.queryPowerSum(x, y) / (y - x + 1);
            double res2 = res1 - avg * avg;
            int r = int(res2 * 100);
            cout << r << "\n";
        }
    }
    return 0;
}