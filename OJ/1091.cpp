//
// Created by Rainy Memory on 2021/3/14.
//

#include <cstdio>

#define MAXN 1003007

int visited[2005] = {0};
int gallery[MAXN] = {0};
int start[MAXN] = {0}, end[MAXN] = {0};
int head = 0, tail = 0, n, m, cnt = 0, min = 10000000;
bool addFlag, fullFlag = false;

inline void read(int &o) {
    char c = getchar();
    while (c > '9' || c < '0')c = getchar();
    o = 0;
    while (c <= '9' && c >= '0')o = (o << 3) + (o << 1) + c - '0', c = getchar();
}

int main() {
    read(n), read(m);
    for (int i = 0; i < n; i++)read(gallery[i]);
    while (tail < n) {
        addFlag = false;
        if (head == tail || visited[gallery[tail]] == 0)addFlag = true;
        visited[gallery[tail++]]++;
        while (head < tail && visited[gallery[head]] > 1)visited[gallery[head++]]--;
        if (addFlag && ++cnt == m)fullFlag = true;
        if (fullFlag && tail - head < min && start[min = tail - head] == 0)start[min] = head + 1, end[min] = tail;
    }
    printf("%d %d\n", start[min], end[min]);
    return 0;
}