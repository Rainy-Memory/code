//
// Created by Rainy Memory on 2021/3/15.
//

#include <cstdio>

inline void read(int &o) {
    char c = getchar();
    bool neg = false;
    while (c > '9' || c < '0') {
        if (c == '-')neg = true;
        c = getchar();
    }
    o = 0;
    while (c <= '9' && c >= '0')o = (o << 3) + (o << 1) + c - '0', c = getchar();
    if (neg)o *= -1;
}

#define maxn 2000007

int message[maxn] = {0};
int prefix[maxn] = {0};
int MonotoneQueue[maxn] = {0};
int min[maxn] = {0};
int n, nn, head = 0, tail = 0, answer = 0;

int main() {
    read(n);
    nn = (n << 1) - 1;
    for (int i = 1; i <= n; i++)read(message[i]), message[i + n] = message[i];
    for (int i = 1; i <= nn; i++)prefix[i] += message[i] + prefix[i - 1];
    for (int i = 1; i <= nn; i++) {
        while (head < tail && prefix[MonotoneQueue[tail - 1]] >= prefix[i])tail--;
        MonotoneQueue[tail++] = i;
        while (MonotoneQueue[head] <= i - n)head++;
        if (i >= n)min[i] = prefix[MonotoneQueue[head]];
    }
    for (int i = n; i <= nn; i++)
        if (min[i] >= prefix[i - n])answer++;
    printf("%d\n", answer);
    return 0;
}