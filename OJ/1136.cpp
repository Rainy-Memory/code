//
// Created by RainyMemory on 2021/4/15.
//

#include <iostream>

using namespace std;

template<class T>
class vector {
private:
    int capacity = 10;
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
    
    T &operator[](int index) {
        return store[index];
    }
    
    const T &operator[](int index) const {
        return store[index];
    }
    
    int length() const {
        return tail;
    }
};

#define maxn 100007
int n, x, y;
vector<int> graph[maxn];
bool visited[maxn] = {false};

double dfs(int now, int fa, int depth, double now_possibility) {
    if (fa != -1 && graph[now].length() == 1) {
        return depth * now_possibility;
    }
    double ret = 0;
    int num = fa == -1 ? graph[now].length() : graph[now].length() - 1;
    for (int i = 0; i < graph[now].length(); i++) {
        if (graph[now][i] != fa) {
            ret += dfs(graph[now][i], now, depth + 1, now_possibility / num);
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    printf("%.15lf\n", dfs(1, -1, 0, 1));
    return 0;
}