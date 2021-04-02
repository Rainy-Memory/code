//
// Created by Rainy Memory on 2021/3/29.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

template<class T>
inline void read(T &o) {
    char c = getchar();
    while (c < '0' || c > '9')c = getchar();
    o = 0;
    while (c >= '0' && c <= '9')o = (o << 3) + (o << 1) + c - '0', c = getchar();
}

struct Edge {
    int v = -1;
    Edge *next = nullptr;
    
    Edge(int _v, Edge *_next) : v(_v), next(_next) {}
};

Edge *graph[107] = {nullptr};
bool visited[107] = {false};
int n, m, start, path_len, x, y, cnt = 0;

void dfs(int pos, int now_len) {
    if (visited[pos])return;
    visited[pos] = true;
    if (now_len == path_len)cnt++;
    else for (Edge *i = graph[pos]; i != nullptr; i = i->next)dfs(i->v, now_len + 1);
    visited[pos] = false;
}

int main() {
    read(n), read(m), read(start), read(path_len);
    for (int i = 0; i < m; i++) {
        read(x), read(y);
        graph[x] = new Edge(y, graph[x]);
    }
    dfs(start, 0);
    printf("%d\n", cnt);
    return 0;
}