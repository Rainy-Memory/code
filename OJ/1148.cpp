//
// Created by Rainy Memory on 2021/4/29.
//

#include <iostream>
#include <cmath>

using namespace std;

#define maxn 1000007

int cnt = 0;
int map[maxn], trie[maxn][26] = {0};
int lg[maxn], lca_father[maxn][20], depth[maxn];
int command[maxn][12];
bool is_2[maxn] = {false};

int insert(const string &s) {
    int l = int(s.length()), p = 0;
    for (int i = l - 1; i >= 0; i--) {
        if (trie[p][s[i] - 'a'] == 0)trie[p][s[i] - 'a'] = ++cnt;
        p = trie[p][s[i] - 'a'];
    }
    return p;
}

void dfs(int now, int pa) {
    depth[now] = pa == -1 ? 0 : depth[pa] + 1;
    lca_father[now][0] = pa;
    for (int i = 1; i <= lg[depth[now]]; i++)lca_father[now][i] = lca_father[lca_father[now][i - 1]][i - 1];
    for (int i = 0; i < 26; i++)
        if (trie[now][i] != 0)dfs(trie[now][i], now);
}

int find_lca(int a, int b) {
    if (depth[a] < depth[b])swap(a, b);
    while (depth[a] > depth[b])a = lca_father[a][lg[depth[a] - depth[b]]];
    if (a == b)return a;
    for (int i = lg[depth[a]]; i >= 0; i--)
        if (lca_father[a][i] != lca_father[b][i])a = lca_father[a][i], b = lca_father[b][i];
    return lca_father[a][0];
}

int main() {
    ios::sync_with_stdio(false);
    int n, m, op, word_cnt = 0;
    string str;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> str;
        map[++word_cnt] = insert(str);
    }
    for (int i = 0; i < m; i++) {
        cin >> op;
        if (op == 1) {
            cin >> str;
            map[++word_cnt] = insert(str);
        }
        else {
            is_2[i] = true;
            cin >> command[i][0];
            for (int j = 1; j <= command[i][0]; j++)cin >> command[i][j];
        }
    }
    for (int i = 1; i <= 10007; i++)lg[i] = int(log(i) / log(2));
    dfs(0, -1);
    int lca;
    for (int i = 0; i < m; i++) {
        if (is_2[i]) {
            lca = map[command[i][1]];
            for (int j = 2; j <= command[i][0]; j++)lca = find_lca(lca, map[command[i][j]]);
            cout << depth[lca] << endl;
        }
    }
    return 0;
}