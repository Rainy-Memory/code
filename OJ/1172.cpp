//
// Created by Rainy Memory on 2021/5/11.
//

#include <iostream>

using namespace std;

#define maxn 10007
int fa[maxn];

int find(int x) {
    if (fa[x] != x) {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

int main() {
    ios::sync_with_stdio(false);
    int n, m, z, x, y;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    while (m--) {
        cin >> z >> x >> y;
        x = find(x);
        y = find(y);
        if (z == 1) {
            fa[x] = y;
        }
        else {
            if (x == y)cout << "Y" << endl;
            else cout << "N" << endl;
        }
    }
    return 0;
}
