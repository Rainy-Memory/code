//
// Created by Rainy Memory on 2021/4/2.
//

#include <cstdio>
#include <cmath>

template<class T>
inline void read(T &o) {
    char c = getchar();
    while (c < '0' || c > '9')c = getchar();
    o = 0;
    while (c >= '0' && c <= '9')o = (o << 3) + (o << 1) + c - '0', c = getchar();
}

struct edge {
    int v = -1;
    int w = -1;
    
    edge() = default;
    
    edge(int vv, int ww) : v(vv), w(ww) {}
};

template<class T>
class vector {
private:
    T *store;
    int capacity = 10;
    int tail = 0;
    
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
    
    void push_back(T o) {
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

int n, m, x, y, w, op, u, v, res;
vector<edge> graph[maxn];
int depth[maxn];
int lg[maxn];
int lca_father[maxn][20];
int lca_add[maxn][20];
int lca_xor[maxn][20];

void swap(int &a, int &b) {
    int t = a;
    a = b, b = t;
}

void dfs(int now, int father, int weight) {
    depth[now] = depth[father] + 1;
    lca_father[now][0] = father, lca_add[now][0] = lca_xor[now][0] = weight;
    for (int i = 1; i <= lg[depth[now]]; i++) {
        lca_father[now][i] = lca_father[lca_father[now][i - 1]][i - 1];
        lca_add[now][i] = lca_add[lca_father[now][i - 1]][i - 1] + lca_add[now][i - 1];
        lca_xor[now][i] = lca_xor[lca_father[now][i - 1]][i - 1] ^ lca_xor[now][i - 1];
    }
    for (int i = 0; i < graph[now].size(); i++)
        if (graph[now][i].v != father)dfs(graph[now][i].v, now, graph[now][i].w);
}

void lca(int a, int b) {
    res = 0;
    if (depth[a] < depth[b])swap(a, b);
    while (depth[a] > depth[b]) {
        if (op == 0)res ^= lca_xor[a][lg[depth[a] - depth[b]]];
        else res += lca_add[a][lg[depth[a] - depth[b]]];
        a = lca_father[a][lg[depth[a] - depth[b]]];
    }
    if (a == b)return;
    for (int i = lg[depth[a]]; i >= 0; i--)
        if (lca_father[a][i] != lca_father[b][i]) {
            if (op == 0)res ^= lca_xor[a][i] ^ lca_xor[b][i];
            else res += lca_add[a][i] + lca_add[b][i];
            a = lca_father[a][i], b = lca_father[b][i];
        }
    if (op == 0)res ^= lca_xor[a][0] ^ lca_xor[b][0];
    else res += lca_add[a][0] + lca_add[b][0];
}

int main() {
    read(n), read(m);
    for (int i = 0; i < n - 1; i++) {
        read(x), read(y), read(w);
        graph[x].push_back(edge(y, w));
        graph[y].push_back(edge(x, w));
    }
    for (int i = 1; i <= n; i++)lg[i] = int(log(i) / log(2));
    depth[0] = 0;
    dfs(1, 0, 0);
    for (int i = 0; i < m; i++) {
        read(op), read(u), read(v);
        lca(u, v);
        printf("%d\n", res);
    }
    return 0;
}