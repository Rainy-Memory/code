//
// Created by Rainy Memory on 2021/3/18.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

inline void read(int &o) {
    o = 0;
    char c = getchar();
    while (c > '9' || c < '0')c = getchar();
    while (c <= '9' && c >= '0')o = (o << 3) + (o << 1) + c - '0', c = getchar();
}

int partition(int *a, int l, int r) {
    int temp = a[l];
    while (l < r) {
        while (l < r && a[r] >= temp)r--;
        if (l < r)a[l] = a[r], l++;
        while (l < r && a[l] <= temp)l++;
        if (l < r)a[r] = a[l], r--;
    }
    a[r] = temp;
    return r;
}

void quick_sort(int *a, int l, int r) {
    if (l >= r)return;
    int mid = partition(a, l, r);
    quick_sort(a, l, mid - 1);
    quick_sort(a, mid + 1, r);
}

int n;
int a[1000007];

int main() {
    read(n);
    for (int i = 0; i < n; i++)read(a[i]);
    quick_sort(a, 0, n - 1);
    for (int i = 0; i < n; i++) {
        if (i == 0 || a[i - 1] != a[i])printf("%d ", a[i]);
    }
    puts("");
    return 0;
}