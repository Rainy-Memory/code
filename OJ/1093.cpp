//
// Created by Rainy Memory on 2021/3/15.
//

#include <cstdio>

int n, m, a, head, tail, min = 2000000000;
int h[1005][1005] = {0};
int condensed[1005][1005] = {0};
int result[1005][1005] = {0};
int condensed2[1005][1005] = {0};
int result2[1005][1005] = {0};
int MonotoneQueue[1005] = {0};

inline void read(int &o) {
    char c = getchar();
    while (c > '9' || c < '0')c = getchar();
    o = 0;
    while (c <= '9' && c >= '0')o = (o << 3) + (o << 1) + c - '0', c = getchar();
}

inline int minint(int c, int b) {
    return c < b ? c : b;
}

int main() {
    read(n), read(m), read(a);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            read(h[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        head = tail = 0;
        for (int j = 0; j < m; j++) {
            while (head < tail && h[i][MonotoneQueue[tail - 1]] >= h[i][j])tail--;
            MonotoneQueue[tail++] = j;
            while (MonotoneQueue[head] <= j - a)head++;
            if (j >= a - 1)condensed[i][j - a + 1] = h[i][MonotoneQueue[head]];
        }
    }
    //condensed: n * (m - a + 1)
    for (int j = 0; j < m - a + 1; j++) {
        head = tail = 0;
        for (int i = 0; i < n; i++) {
            while (head < tail && condensed[MonotoneQueue[tail - 1]][j] >= condensed[i][j])tail--;
            MonotoneQueue[tail++] = i;
            while (MonotoneQueue[head] <= i - a)head++;
            if (i >= a - 1)result[i - a + 1][j] = condensed[MonotoneQueue[head]][j];
        }
    }
    //result: (n - a + 1) * (m - a + 1)
    for (int i = 0; i < n; i++) {
        head = tail = 0;
        for (int j = 0; j < m; j++) {
            while (head < tail && h[i][MonotoneQueue[tail - 1]] <= h[i][j])tail--;
            MonotoneQueue[tail++] = j;
            while (MonotoneQueue[head] <= j - a)head++;
            if (j >= a - 1)condensed2[i][j - a + 1] = h[i][MonotoneQueue[head]];
        }
    }
    for (int j = 0; j < m - a + 1; j++) {
        head = tail = 0;
        for (int i = 0; i < n; i++) {
            while (head < tail && condensed2[MonotoneQueue[tail - 1]][j] <= condensed2[i][j])tail--;
            MonotoneQueue[tail++] = i;
            while (MonotoneQueue[head] <= i - a)head++;
            if (i >= a - 1)result2[i - a + 1][j] = condensed2[MonotoneQueue[head]][j];
        }
    }
    for (int i = 0; i < n - a + 1; i++) {
        for (int j = 0; j < m - a + 1; j++) {
            min = minint(min, result2[i][j] - result[i][j]);
        }
    }
    printf("%d\n", min);
    return 0;
}