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

int n, m, nowLength, nowPos, nextPos, step;
bool faceRight = true;
BinaryIndexTree *bit;

int binarySearch(int target) {
    int l = 1, r = n, erasePos = -1;
    while (true) {
        if (r - l < 3) {
            for (int i = l; i <= r; i++) {
                int num = bit->rangeSum(1, i);
                if (num == target) {
                    erasePos = i;
                    break;
                }
            }
            break;
        }
        else {
            int mid = (l + r) >> 1;
            int num = bit->rangeSum(1, mid);
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
    bit = new BinaryIndexTree(n);
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
        bit->update(erasePos, -1);
        nowPos = nextPos;
        nowLength--;
        if (!faceRight)nowPos--;
    }
    int result = binarySearch(1);
    cout << result << endl;
    delete bit;
    return 0;
}