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
    int size;
    T *addTag;
    T *multiTag;
    
    inline void push_up(int p) {
        tree[p] = tree[p << 1] + tree[p << 1 | 1];
    }
    
    inline void push_down(int p, int s, int t) {
        if (multiTag[p] != 1) {
            multiTag[p << 1] *= multiTag[p];
            multiTag[p << 1 | 1] *= multiTag[p];
            addTag[p << 1] *= multiTag[p];
            addTag[p << 1 | 1] *= multiTag[p];
            tree[p << 1] *= multiTag[p];
            tree[p << 1 | 1] *= multiTag[p];
            multiTag[p] = 1;
        }
        if (addTag[p] != 0) {
            int m = (s + t) >> 1;
            addTag[p << 1] += addTag[p];
            addTag[p << 1 | 1] += addTag[p];
            tree[p << 1] += addTag[p] * (m - s + 1);
            tree[p << 1 | 1] += addTag[p] * (t - m);
            addTag[p] = 0;
        }
    }
    
    void inner_build(T *a, int s, int t, int p) {
        addTag[p] = 0, multiTag[p] = 1;
        if (s == t) {
            tree[p] = a[s];
            return;
        }
        int m = (s + t) >> 1;
        inner_build(a, s, m, p << 1);
        inner_build(a, m + 1, t, p << 1 | 1);
        push_up(p);
    }
    
    void inner_add(int l, int r, int s, int t, int p, T v) {
        if (l <= s && t <= r) {
            addTag[p] += v;
            tree[p] += v * (t - s + 1);
            return;
        }
        int m = (s + t) >> 1;
        if (addTag[p] != 0 || multiTag[p] != 1)push_down(p, s, t);
        if (l <= m)inner_add(l, r, s, m, p << 1, v);
        if (m < r)inner_add(l, r, m + 1, t, p << 1 | 1, v);
        push_up(p);
    }
    
    void inner_multi(int l, int r, int s, int t, int p, T v) {
        if (l <= s && t <= r) {
            multiTag[p] *= v;
            addTag[p] *= v;
            tree[p] *= v;
            return;
        }
        int m = (s + t) >> 1;
        if (addTag[p] != 0 || multiTag[p] != 1)push_down(p, s, t);
        if (l <= m)inner_multi(l, r, s, m, p << 1, v);
        if (m < r)inner_multi(l, r, m + 1, t, p << 1 | 1, v);
        push_up(p);
    }
    
    T inner_sum(int l, int r, int s, int t, int p) {
        if (l <= s && t <= r)return tree[p];
        T ret(0);
        int m = (s + t) >> 1;
        if (addTag[p] != 0 || multiTag[p] != 1)push_down(p, s, t);
        if (l <= m)ret += inner_sum(l, r, s, m, p << 1);
        if (m < r)ret += inner_sum(l, r, m + 1, t, p << 1 | 1);
        return ret;
    }

public:
    SegmentTree(T *a, int n) : size(n) {
        tree = new T[size << 2];
        addTag = new T[size << 2];
        multiTag = new T[size << 2];
        inner_build(a, 1, size, 1);
    }
    
    void rangeAdd(int l, int r, T v) {
        inner_add(l, r, 1, size, 1, v);
    }
    
    void rangeMulti(int l, int r, T v) {
        inner_multi(l, r, 1, size, 1, v);
    }
    
    T querySum(int l, int r) {
        return inner_sum(l, r, 1, size, 1);
    }
};

SegmentTree<int> *letterSegmentTree[26];
char str[100007], c;
int letter[26][100007];
int n, m, x, l, r, pos, num;

int main() {
    read(n), read(m);
    scanf("%s", str);
    for (int i = 0; i < n; i++)letter[str[i] - 'a'][i + 1]++;
    for (int i = 0; i < 26; i++)letterSegmentTree[i] = new SegmentTree<int>(letter[i], n);
    while (m--) {
        read(l), read(r), read(x);
        pos = l;
        for (int i = 0; i < 26; i++) {
            int index = x == 1 ? i : 25 - i;
            num = letterSegmentTree[index]->querySum(l, r);
            if (num == 0)continue;
            letterSegmentTree[index]->rangeMulti(l, r, 0);
            letterSegmentTree[index]->rangeAdd(pos, pos + num - 1, 1);
            for (int j = pos - 1; j < pos + num - 1; j++)str[j] = char('a' + index);
            pos += num;
        }
    }
    printf("%s\n", str);
    return 0;
}