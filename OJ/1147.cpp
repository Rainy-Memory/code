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
};

int n, root = 1, res = -1;
tree_node node[maxn];

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

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++)cin >> node[i].value;
    for (int i = 1; i <= n; i++)cin >> node[i].left >> node[i].right;
    dfs_child_num(root);
    for (int i = 1; i <= n; i++) {
        if (symmetry(node[i].left, node[i].right))res = max(res, node[i].child_num);
    }
    cout << res << endl;
    return 0;
}