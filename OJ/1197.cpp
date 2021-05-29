//
// Created by Rainy Memory on 2021/5/28.
//

#include <iostream>

using namespace std;

#define maxn 500007
typedef long long ll;

template<class T>
class vector {
private:
    int capacity = 2;
    int tail = 0;
    T *store = nullptr;
    
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
    
    T &operator[](int i) {
        return store[i];
    }
    
    const T &operator[](int i) const {
        return store[i];
    }
    
    int size() const {
        return tail;
    }
};

vector<int> old_graph[maxn];
vector<pair<int, int>> new_graph[maxn];
int dfn[maxn] = {0}, low[maxn] = {0}, dfn_cnt = 0, stack[maxn], top = 0, queue[maxn];
int scc[maxn], sc = 0;
ll w[maxn], money[maxn], res[maxn] = {0};
bool in_stack[maxn], in_queue[maxn];

inline void tarjan(int u) {
    dfn[u] = low[u] = ++dfn_cnt;
    stack[top++] = u;
    in_stack[u] = true;
    for (int i = 0; i < old_graph[u].size(); i++) {
        int v = old_graph[u][i];
        if (dfn[v] == 0)tarjan(v), low[u] = min(low[u], low[v]);
        else if (in_stack[v])low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        sc++;
        do {
            top--;
            scc[stack[top]] = sc;
            money[sc] += w[stack[top]];
            in_stack[stack[top]] = false;
        } while (stack[top] != u);
    }
}

inline void spfa(int s) {
    int head = 0, tail = 0, u, v;
    queue[tail++] = s;
    in_queue[s] = true;
    res[s] = money[s];
    while (head < tail) {
        u = queue[head++];
        in_queue[u] = false;
        for (int i = 0; i < new_graph[u].size(); i++) {
            v = new_graph[u][i].first;
            ll r = new_graph[u][i].second;
            if (res[v] < res[u] + r) {
                res[v] = res[u] + r;
                if (!in_queue[v]) {
                    queue[tail++] = v;
                    in_queue[v] = true;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    int n, m, u, v, s, p, bar;
    ll ans = -1;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        old_graph[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)cin >> w[i];
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)tarjan(i);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < old_graph[i].size(); j++) {
            v = old_graph[i][j];
            if (scc[i] != scc[v]) {
                new_graph[scc[i]].push_back({scc[v], money[scc[v]]});
            }
        }
    }
    cin >> s >> p;
    spfa(scc[s]);
    while (p--) {
        cin >> bar;
        ans = max(ans, res[scc[bar]]);
    }
    cout << ans << endl;
    return 0;
}