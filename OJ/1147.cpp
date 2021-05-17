//
// Created by Rainy Memory on 2021/4/29.
//

#include <iostream>

using namespace std;

#define maxn 1000007

struct tree_node {
    int value = 0;
    int left = -1;
    int right = -1;
    int child_num = 0;
    long long hash1 = 0;
    long long hash2 = 0;
};

int n, root = 1, res = -1;
tree_node node[maxn];

const long long p = 1e9 + 7;
const long long key = 151, key1 = 157, key2 = 163;

int dfs_child_num(int now) {
    if (now == -1)return 0;
    return node[now].child_num = dfs_child_num(node[now].left) + dfs_child_num(node[now].right) + 1;
}

bool symmetry(int l, int r) {
    if (l == -1 && r == -1)return true;
    if (l == -1 || r == -1)return false;
    if (node[l].value != node[r].value)return false;
    return symmetry(node[l].left, node[r].right) && symmetry(node[l].right, node[r].left);
}

void solve_dfs() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++)cin >> node[i].value;
    for (int i = 1; i <= n; i++)cin >> node[i].left >> node[i].right;
    dfs_child_num(root);
    for (int i = 1; i <= n; i++) {
        if (symmetry(node[i].left, node[i].right))res = max(res, node[i].child_num);
    }
    cout << res << endl;
}

void dfs(int now) {
    node[now].hash1 = node[now].hash2 = node[now].value;
    if (node[now].left != -1)dfs(node[now].left);
    if (node[now].right != -1)dfs(node[now].right);
    node[now].hash1 = (node[now].hash1 * node[now].child_num + node[node[now].left].hash1 * key1 + node[node[now].right].hash1 * key2) % p;
    node[now].hash2 = (node[now].hash2 * node[now].child_num + node[node[now].right].hash2 * key1 + node[node[now].left].hash2 * key2) % p;
    if (node[node[now].left].hash1 == node[node[now].right].hash2 && node[node[now].left].hash2 == node[node[now].right].hash1)
        res = max(res, node[now].child_num);
}

void solve_hash() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++)cin >> node[i].value;
    for (int i = 1; i <= n; i++)cin >> node[i].left >> node[i].right;
    dfs_child_num(root);
    dfs(root);
    cout << res << endl;
}

int main() {
//    solve_dfs();
    solve_hash();
    return 0;
}