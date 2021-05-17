//
// Created by Rainy Memory on 2021/4/2.
//

/*
#include <cstdio>
#include <cmath>

template<class T>
inline void read(T &o) {
    char c = getchar();
    while (c < '0' || c > '9')c = getchar();
    o = 0;
    while (c >= '0' && c <= '9')o = (o << 3) + (o << 1) + c - '0', c = getchar();
}

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

#define maxn 500007

int n, m, s, x, y;
vector<int> graph[maxn];
int depth[maxn];
int lg[maxn];
int lca_father[maxn][20];

void swap(int &a, int &b) {
    int t = a;
    a = b, b = t;
}

void dfs(int now, int father) {
    depth[now] = depth[father] + 1;
    lca_father[now][0] = father;
    for (int i = 1; i <= lg[depth[now]]; i++)
        lca_father[now][i] = lca_father[lca_father[now][i - 1]][i - 1];
    for (int i = 0; i < graph[now].size(); i++)
        if (graph[now][i] != father)dfs(graph[now][i], now);
}

int lca(int a, int b) {
    if (depth[a] < depth[b])swap(a, b);
    while (depth[a] > depth[b])
        a = lca_father[a][lg[depth[a] - depth[b]]];
    if (a == b)return a;
    for (int i = lg[depth[a]]; i >= 0; i--) {
        if (lca_father[a][i] != lca_father[b][i])a = lca_father[a][i], b = lca_father[b][i];
    }
    return lca_father[a][0];
}

int main() {
    read(n), read(m), read(s);
    for (int i = 0; i < n - 1; i++) {
        read(x), read(y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)lg[i] = int(log(i) / log(2));
    depth[0] = 0;
    dfs(s, 0);
    int a, b;
    for (int i = 0; i < m; i++) {
        read(a), read(b);
        printf("%d\n", lca(a, b));
    }
    return 0;
}
*/

#include <cstdio>
#include <cmath>

template<class T>
inline void read(T &o) {
    char c = getchar();
    while (c < '0' || c > '9')c = getchar();
    o = 0;
    while (c >= '0' && c <= '9')o = (o << 3) + (o << 1) + c - '0', c = getchar();
}

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

#define maxn 500007

int n, m, s, x, y;
vector<int> graph[maxn];
int depth[maxn];
int lca_father[maxn][21];

void swap(int &a, int &b) {
    int t = a;
    a = b, b = t;
}

void dfs(int now, int father) {
    depth[now] = depth[father] + 1;
    lca_father[now][0] = father;
    for (int i = 1; i <= 20; i++) {
        lca_father[now][i] = lca_father[lca_father[now][i - 1]][i - 1];
    }
    for (int i = 0; i < graph[now].size(); i++) {
        if (graph[now][i] != father) {
            dfs(graph[now][i], now);
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b])swap(a, b);
    //depth[a] > depth[b]
    for (int i = 20; i >= 0; i--) {
        if (depth[lca_father[a][i]] >= depth[b])a = lca_father[a][i];
    }
    if (a == b)return a;
    for (int i = 20; i >= 0; i--) {
        if (lca_father[a][i] != lca_father[b][i])a = lca_father[a][i], b = lca_father[b][i];
    }
    return lca_father[a][0];
}

int main() {
    read(n), read(m), read(s);
    for (int i = 0; i < n - 1; i++) {
        read(x), read(y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    depth[0] = 0;
    dfs(s, 0);
    int a, b;
    for (int i = 0; i < m; i++) {
        read(a), read(b);
        printf("%d\n", lca(a, b));
    }
    return 0;
}