//
// Created by Rainy Memory on 2021/2/26.
//

#include <iostream>
#include <cstddef>
#include <functional>
#include <cstring>
#include <string>

using namespace std;

#define MAXN 6000007

int order[MAXN] = {0};
int w[MAXN] = {0};
int pre[MAXN] = {0};
int nxt[MAXN] = {0};
bool deleted[MAXN] = {false};
int ans[MAXN] = {0};//if(erase[i]) { ans[i] == erased element's weight }, -1 represent query max weight, others is ans.
bool invalid[MAXN] = {false};
bool erase[MAXN] = {false};//No.i operation is erase a number.

inline void read(int &o) {
    char c = getchar();
    bool negative = false;
    while (c > '9' || c < '0') {
        if (c == '-')negative = true;
        c = getchar();
    }
    o = 0;
    while (c <= '9' && c >= '0') {
        o = o * 10 + c - '0';
        c = getchar();
    }
    if (negative)o *= -1;
}

void solveBig(int n) {
    //todo debug... still WA, can only handle huge data
    int q;
    for (int i = 1; i <= n; i++) {
        read(w[i]);
        pre[i] = i == 1 ? n : i - 1;
        nxt[i] = i == n ? 1 : i + 1;
    }
    read(q);
    int op, x;
    for (int i = 1; i <= q; i++) {
        read(op);
        if (op == 0) {
            read(x);
            if (!deleted[x]) {
                deleted[x] = true;
                nxt[pre[x]] = nxt[x];
                pre[nxt[x]] = pre[x];
                nxt[x] = -1;
                pre[x] = -1;
                ans[i] = w[x];
                erase[i] = true;
            }
            else invalid[i] = true;
        }
        else if (op == 1) {
            char opt = getchar();
            while (true) {
                if (opt == 'P' || opt == 'N')break;
                opt = getchar();
            }
            read(x);
            if (opt == 'P') {
                if (deleted[x])invalid[i] = true;
                else ans[i] = pre[x];
            }
            else {
                if (deleted[x])invalid[i] = true;
                else ans[i] = nxt[x];
            }
        }
        else ans[i] = -1;
    }
    int maxNum = -1;
    for (int i = 1; i <= n; i++) {
        if (!deleted[i] && maxNum < w[i])maxNum = w[i];
    }
    for (int i = q; i > 0; i--) {
        if (!invalid[i]) {
            if (ans[i] == -1) {
                if (maxNum != -1)ans[i] = maxNum;
                else invalid[i] = true;
            }
            else if (erase[i]) {
                if (maxNum < ans[i])maxNum = ans[i];
            }
        }
    }
    for (int i = 1; i <= q; i++) {
        if (invalid[i] && !erase[i])puts("Invalid.");
        else if (!erase[i])printf("%d\n", ans[i]);
    }
}

template<class T>
int divide(T *array, int low, int high, bool (*compare)(T, T)) {
    T temp = array[low];
    while (low < high) {
        while (low < high && !(compare(array[high], temp)))high--;
        if (low < high)array[low] = array[high], low++;
        while (low < high && (compare(array[low], temp) || (!compare(array[low], temp) && !compare(temp, array[low]))))low++;
        if (low < high)array[high] = array[low], high--;
    }
    array[low] = temp;
    return low;
}

template<class T>
void quickSort(T *array, int low, int high, bool (*compare)(T, T)) {
    if (low >= high)return;
    int mid = divide(array, low, high, compare);
    quickSort(array, low, mid - 1, compare);
    quickSort(array, mid + 1, high, compare);
}

bool cmp(int a, int b) {
    return w[a] < w[b];
}

void solveSort(int n) {
    int tail = n;
    int q;
    for (int i = 1; i <= n; i++) {
        read(w[i]);
        pre[i] = i == 1 ? n : i - 1;
        nxt[i] = i == n ? 1 : i + 1;
        order[i] = i;
    }
    quickSort(order, 1, n, cmp);
    read(q);
    int op, x;
    for (int i = 0; i < q; i++) {
        read(op);
        if (op == 0) {
            read(x);
            if (!deleted[x]) {
                deleted[x] = true;
                nxt[pre[x]] = nxt[x];
                pre[nxt[x]] = pre[x];
            }
        }
        else if (op == 1) {
            char opt = getchar();
            while (true) {
                if (opt == 'P' || opt == 'N')break;
                opt = getchar();
            }
            read(x);
            if (opt == 'P') {
                if (deleted[x])puts("Invalid.");
                else printf("%d\n", pre[x]);
            }
            else {
                if (deleted[x])puts("Invalid.");
                else printf("%d\n", nxt[x]);
            }
        }
        else {
            while (tail > 0 && deleted[order[tail]])tail--;
            if (tail == 0)puts("Invalid.");
            else printf("%d\n", w[order[tail]]);
        }
    }
}

int main() {
    int n;
    read(n);
    if (n <= 1000000)solveSort(n);
    else solveBig(n);
    return 0;
}