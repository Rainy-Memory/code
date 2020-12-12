#include <iostream>
#include <cstring>

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
int *&funA(int **&x) {
    x = new int *;
    //*x=new int[n];
    return (*x);
}

void funB(int *c, int **x, int **y) {
    for (int i = 0; i < n; i++) {
        c[i] = (*x)[i] * (*y)[i];
    }
    delete x;
    delete y;
}