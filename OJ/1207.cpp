//
// Created by Rainy Memory on 2021/5/24.
//

#include <iostream>

using namespace std;

#define maxn 100007
int fa[maxn << 1];//0 represent same, 1 represent diff

//int find(int x) {
//    if (x == fa[x])return x;
//    int xx = find(fa[x]);
//    dist[x] ^= dist[fa[x]];
//    return fa[x] = xx;
//}
//
//void union_set(int x, int y, int target) {
//    int xx = find(x), yy = find(y);
//    dist[xx] ^= dist[x] ^ dist[y] ^ target;
//    fa[xx] = yy;
//}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void union_set(int u, int v) {
    u = find(u), v = find(v);
    if (u == v)return;
    fa[u] = v;
}

int main() {
    int n, q, l, r;
    string type;
    cin >> n >> q;
    for (int i = 1; i <= (n << 1 | 1); i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= q; i++) {
        cin >> l >> r >> type;
        l--;
        int l1 = find(l), r1 = find(r);
        int l2 = find(l + n + 1), r2 = find(r + n + 1);
        if (type == "even") {
            if (l1 == r2 || r1 == l2) {
                cout << i << endl;
                return 0;
            }
            fa[l1] = r1;
            fa[l2] = r2;
        }
        else {
            if (l1 == r1 || l2 == r2) {
                cout << i << endl;
                return 0;
            }
            fa[l1] = r2;
            fa[l2] = r1;
        }
    }
    cout << "-1" << endl;
    return 0;
}