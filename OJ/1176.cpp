//
// Created by Rainy Memory on 2021/5/11.
//

#include <iostream>

using namespace std;

#define maxn 200007
int n, t, res = maxn, depth;
int fa[maxn];

int find(int now) {
    depth++;
    if (fa[now] == now)return now;
    else return find(fa[now]);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++)fa[i] = i;
    for (int i = 1; i <= n; i++) {
        cin >> t;
        depth = 0;
        int temp = find(t);
        if (temp == i)res = min(res, depth);
        else fa[i] = t;
    }
    cout << res << endl;
    return 0;
}