//
// Created by Rainy Memory on 2021/4/2.
//

#include <climits>
#include <cstddef>
#include <cstdio>
#include <iostream>

class BinaryIndexTree {
private:
    int *tree;
    int len;
    
    inline int lowbit(int x) {
        return x & -x;
    }

public:
    BinaryIndexTree(int *arr, int _len) : len(_len) {
        tree = new int[len + 1]();
        for (int i = 1; i <= len; i++) {
            tree[i] += arr[i];
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
        return prefixSum(r) - prefixSum(l - 1);
    }
};

int n, m, op, x, y;
int a[600000] = {0};

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)scanf("%d", &a[i]);
    BinaryIndexTree bit(a, n);
    while (m--) {
        scanf("%d", &op);
        if (op == 1) {
            bit.update(x, y);
        }
        else {
            printf("%d\n", bit.rangeSum(x, y));
        }
    }
    return 0;
}