//
// Created by Rainy Memory on 2021/5/24.
//

#include <iostream>

using namespace std;

#define maxn 300
#define maxm 70000
int fa[maxn], size[maxn];
int from[maxm], to[maxm];
bool used[maxn][maxn] = {false};
int res[maxn] = {0};

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void union_set(int x, int y) {
    x = find(x), y = find(y);
    if (x == y)return;
    if (size[x] > size[y])swap(x, y);
    fa[x] = y;
}

int main() {
    ios::sync_with_stdio(false);
    int n, m, k, f, a, b;
    cin >> n >> m >> k >> f;
    for (int i = 1; i <= n; i++)fa[i] = i, size[i] = 1;
    for (int i = 1; i <= m; i++)cin >> from[i] >> to[i];
    for (int i = 1; i <= f; i++) {
        cin >> a >> b;
        union_set(a, b);
    }
    for (int i = 1; i <= m; i++) {
        a = find(from[i]);
        if (!used[a][to[i]]) {
            res[a]++;
            used[a][to[i]] = true;
        }
    }
    int ans = 1000000;
    for (int i = 1; i <= n; i++)
        if(res[i] != 0)ans = min(ans, res[i]);
    ans = min(ans + k, n);
    cout << ans << endl;
    return 0;
}