#include <iostream>
#include <cstring>

using namespace std;

int n;

int *&funA(int **&x);

void funB(int *c, int **p, int **q);

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

int *&funA(int **&x) {
    x = new int *;
    return (*x);
}

void funB(int *c, int **p, int **q) {
    for (int i = 0; i < n; i++) {
        c[i] = (*p)[i] * (*q)[i];
    }
    
    delete q;
    delete p;
}