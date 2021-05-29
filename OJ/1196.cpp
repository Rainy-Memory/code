//
// Created by Rainy Memory on 2021/5/28.
//

#include <iostream>

using namespace std;

#define maxn 10007
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

struct edge {
    int v;
    ll w;
};
int n;
vector<edge> graph[maxn];
int dist[maxn], queue[maxn];
bool in_stack[maxn];

void spfa(int s, ll x) {
    for (int i = 1; i <= n; i++) {
        dist[i] = 2147483647;
    }
    int head = 0, tail = 0;
    queue[tail++] = s;
    dist[s] = 0;
    in_stack[s] = true;
    while (head < tail) {
        int u = queue[head++];
        in_stack[u] = false;
        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i].v;
            ll w = graph[u][i].w;
            if (dist[v] > dist[u] + (w > x ? 1 : 0)) {
                dist[v] = dist[u] + (w > x ? 1 : 0);
                if (!in_stack[v]) {
                    queue[tail++] = v;
                    in_stack[v] = true;
                }
            }
        }
    }
}

int main() {
    int p, k, u, v;
    ll w, l = 0, r = 1e11, mid, ans = -1;
    cin >> n >> p >> k;
    for (int i = 0; i < p; i++) {
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    while (l <= r) {
        mid = (l + r) >> 1;
        spfa(1, mid);
        if (dist[n] <= k)r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    cout << ans << endl;
    return 0;
}