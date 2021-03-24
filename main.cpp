//
// Created by Rainy Memory on 2021/1/9.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <map>
#include <ctime>

using namespace std;

int n;

// 写出两个函数的声明
int *&funA(int **&);

void funB(int *, int **, int **);

int main() {
    int a[100], b[100], c[100];
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        cin >> b[i];
    int **p, **q;
    funA(p) = a;
    funA(q) = b;
    funB(c, p, q);
    for (int i = 0; i < n; ++i)
        cout << c[i] << " ";
    return 0;
}

// 写出两个函数的定义

int *&funA(int **&ptr) {
    ptr = new int *;
    return *ptr;
}

void funB(int *c, int **p, int **q) {
    for (int i = 0; i < n; i++) {
        c[i] = (*p)[i] * (*q)[i];
    }
    delete p;
    delete q;
}