//
// Created by Rainy Memory on 2021/5/10.
//

#include <iostream>
#include <cmath>

using namespace std;
typedef long long ll;

template<class T>
class vector {
private:
    T *store;
    int tail = 0;
    int capacity = 10;
    
    void double_space() {
        T *temp = new T[capacity <<= 1];
        for (int i = 0; i < tail; i++)temp[i] = store[i];
        delete[]store;
        store = temp;
    }

public:
    vector() {
        store = new T[capacity];
    }
    
    ~vector() {
        delete[]store;
    }
    
    void push_back(const T &o) {
        store[tail++] = o;
        if (tail == capacity)double_space();
    }
    
    T &operator[](int index) {
        return store[index];
    }
    
    const T &operator[](int index) const {
        return store[index];
    }
    
    int size() const {
        return tail;
    }
};

#define maxn 100007
vector<int> graph[maxn];
int milktea[maxn] = {0};
int depth[maxn];
int lca_fa[maxn][21];

void dfs(int now, int father) {
    depth[now] = depth[father] + 1;
    lca_fa[now][0] = father;
    for (int i = 1; i <= 20; i++) {
        lca_fa[now][i] = lca_fa[lca_fa[now][i - 1]][i - 1];
    }
    for (int i = 0; i < graph[now].size(); i++) {
        if (graph[now][i] != father)dfs(graph[now][i], now);
    }
}

void swap(int &o1, int &o2) {
    int temp(o2);
    o2 = o1, o1 = temp;
}

int find_lca(int a, int b) {
    if (depth[a] < depth[b])swap(a, b);
    for (int i = 20; i >= 0; i--) {
        if (depth[lca_fa[a][i]] >= depth[b])a = lca_fa[a][i];
    }
    if (a == b)return a;
    for (int i = 20; i >= 0; i--) {
        if (lca_fa[a][i] != lca_fa[b][i])a = lca_fa[a][i], b = lca_fa[b][i];
    }
    return lca_fa[a][0];
}

int max(int a, int b) {
    return a < b ? b : a;
}

int main() {
    int n, k, u, v, s, t;
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    depth[0] = 0;
    dfs(1, 0);//root == 1
    for (int i = 0; i < k; i++) {
        cin >> s >> t;
        int lca = find_lca(s, t);
        while (s != lca) {
            milktea[s]++;
            s = lca_fa[s][0];
        }
        while (t != lca) {
            milktea[t]++;
            t = lca_fa[t][0];
        }
        milktea[lca]++;
    }
    int max_num = -1;
    for (int i = 1; i <= n; i++) {
        max_num = max(max_num, milktea[i]);
    }
    cout << max_num << endl;
    return 0;
}