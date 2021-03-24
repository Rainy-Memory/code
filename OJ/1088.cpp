//
// Created by Rainy Memory on 2021/2/26.
//

#include <iostream>

using namespace std;

class BinaryIndexTree {
private:
    int *tree;
    int len;
    
    inline int lowbit(int x) {
        return x & -x;
    }

public:
    BinaryIndexTree(int _len) : len(_len) {
        tree = new int[len + 1];
        for (int i = 1; i <= len; i++)tree[i] = 0;
        for (int i = 1; i <= len; i++) {
            tree[i]++;
            int j = i + lowbit(i);
            if (j <= len)tree[j] += tree[i];
        }
    }
    
    ~BinaryIndexTree() {
        delete[]tree;
    }
    
    void update(int index, int value) {
        while (index <= len) {
            tree[index] += value;
            index += lowbit(index);
        }
    }
    
    int prefixSum(int index) {
        int result = 0;
        while (index > 0) {
            result += tree[index];
            index -= lowbit(index);
        }
        return result;
    }
    
    int rangeSum(int l, int r) {
        //return range [l, r] sum
        if (l == 1)return prefixSum(r);
        return prefixSum(r) - prefixSum(l - 1);
    }
};

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

int n, m, nowLength, nowPos, nextPos, step;
bool faceRight = true;
SegmentTree<int> *st;

int binarySearch(int target) {
    int l = 1, r = n, erasePos = -1;
    while (true) {
        if (r - l < 3) {
            for (int i = l; i <= r; i++) {
                int num = st->rangeSum(1, i);
                if (num == target) {
                    erasePos = i;
                    break;
                }
            }
            break;
        }
        else {
            int mid = (l + r) >> 1;
            int num = st->rangeSum(1, mid);
            if (num < target)l = mid + 1;
            else r = mid;
        }
    }
    return erasePos;
}

int main() {
    cin >> n >> m;
    if (m == 1) {
        cout << n << endl;
        return 0;
    }
    int a[100005] = {0};
    for (int i = 1; i <= n; i++)a[i] = 1;
    st = new SegmentTree<int>(a, n);
    nowLength = n;
    nowPos = 1;
    while (nowLength > 1) {
        step = (m - 1) % (2 * nowLength - 2);
        nextPos = nowPos;
        while (true) {
            if (faceRight) {
                if (nextPos + step < nowLength) {
                    nextPos += step;
                    break;
                }
                else if (nextPos + step < nowLength) {
                    nextPos = nowLength;
                    faceRight = false;
                    break;
                }
                else {
                    step -= nowLength - nextPos;
                    nextPos = nowLength;
                    faceRight = false;
                }
            }
            else {
                if (nextPos - step > 1) {
                    nextPos -= step;
                    break;
                }
                else if (nextPos - step == 1) {
                    nextPos = 1;
                    faceRight = true;
                    break;
                }
                else {
                    step -= nextPos - 1;
                    nextPos = 1;
                    faceRight = true;
                }
            }
        }
        int erasePos = binarySearch(nextPos);
        st->update(erasePos, -1);
        nowPos = nextPos;
        nowLength--;
        if (!faceRight)nowPos--;
    }
    int result = binarySearch(1);
    cout << result << endl;
    delete st;
    return 0;
}