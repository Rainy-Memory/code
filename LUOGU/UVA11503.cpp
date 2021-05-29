//
// Created by Rainy Memory on 2021/5/24.
//

#include <iostream>
#include <map>

using namespace std;

#define maxn 200000
int fa[maxn], size[maxn];
map<string, int> mp;

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void union_set(int x, int y) {
    x = find(x), y = find(y);
    if (x == y)return;
    if (size[x] > size[y])swap(x, y);
    fa[x] = y;
    size[y] += size[x];
    cout << size[y] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int t, n, a, b;
    cin >> t;
    string na, nb;
    while (t--) {
        mp.clear();
        cin >> n;
        for (int i = 0; i <= n; i++)fa[i] = i, size[i] = 1;
        while (n--) {
            cin >> na >> nb;
            if (mp.count(na) == 0) {
                int temp = (int) mp.size();
                a = mp[na] = temp;
            }
            if (mp.count(nb) == 0) {
                int temp = (int) mp.size();
                b = mp[nb] = temp;
            }
            union_set(a, b);
        }
    }
    return 0;
}