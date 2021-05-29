//
// Created by Rainy Memory on 2021/5/24.
//

#include <iostream>
#include <map>

using namespace std;

template<class T>
class vector {
private:
    int capacity = 10;
    int tail = 0;
    T *store;
    
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
    
    int length() const {
        return tail;
    }
};

#define maxn 200000
int fa[maxn], size[maxn], close[maxn];
int connected_num = 0;
bool built[maxn] = {false}, result[maxn];
vector<int> graph[maxn];

void add_edge(int x, int y) {
    graph[x].push_back(y);
    graph[y].push_back(x);
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void union_set(int x, int y) {
    x = find(x), y = find(y);
    if (x == y)return;
    if (size[x] > size[y])swap(x, y);
    size[y] += size[x];
    fa[x] = y;
    connected_num--;
}

int main() {
    int n, m, u, v;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        add_edge(u, v);
    }
    for (int i = 0; i < n; i++){
        fa[i] = i, size[i] = 1;
        cin >> close[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        built[close[i]] = true;
        connected_num++;
        for (int j = 0; j < graph[close[i]].length(); j++) {
            if (built[graph[close[i]][j]]) {
                union_set(close[i], graph[close[i]][j]);
            }
        }
        result[i] = connected_num == 1;
    }
    for (int i = 0; i < n; i++) {
        if (result[i])cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}