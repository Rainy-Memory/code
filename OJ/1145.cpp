//
// Created by Rainy Memory on 2021/4/26.
//

/*
#include <iostream>
#include <cmath>

using namespace std;

#define maxn 200007
int n, m, a, b;
int arr[maxn];
int log_2[maxn];
int st[maxn][20];//st[i][j] represent range [i, i + 2 ^ j - 1] max

inline int max(int i, int j) {
    return i < j ? j : i;
}

void initialize_st() {
    for (int i = 0; i <= n; i++)log_2[i] = int(log(i) / log(2));
    for (int i = 0; i < n; i++)st[i][0] = arr[i];
    for (int j = 1; j <= log_2[n]; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int st_max(int l, int r) {
    int lo = log_2[r - l + 1];
    return max(st[l][lo], st[r - (1 << lo) + 1][lo]);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++)cin >> arr[i];
    initialize_st();
    cin >> m;
    while (m--) {
        cin >> a >> b;
        cout << st_max(a - 1, b - 1) << endl;
    }
    return 0;
}
*/
#include <iostream>
#include <cmath>

using namespace std;

#define maxn 200007
int n, m, a, b;
int arr[maxn];
int log_2[maxn];
int st[maxn][20];//st[i][j] represent range [i, i + 2 ^ j - 1] max

inline int max(int i, int j) {
    return i < j ? j : i;
}

void initialize_st() {
    for (int i = 1; i <= n; i++)log_2[i] = int(log(i) / log(2));
    for (int j = 1; j <= log_2[n]; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int st_max(int l, int r) {
    int lg = log_2[r - l + 1];
    return max(st[l][lg], st[r - (1 << lg) + 1][lg]);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++)cin >> st[i][0];
    initialize_st();
    cin >> m;
    while (m--) {
        cin >> a >> b;
        cout << st_max(a - 1, b - 1) << endl;
    }
    return 0;
}
