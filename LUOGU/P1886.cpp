//
// Created by Rainy Memory on 2021/3/12.
//

#include <cstdio>

#define MAXN 1000005

int n, k, head, tail;
int a[MAXN] = {0}, ansMin[MAXN] = {0}, ansMax[MAXN] = {0};
int MonotoneQueue[MAXN] = {0};

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    head = 1, tail = 0;
    for (int i = 0; i < n; i++) {
        while (head <= tail && a[MonotoneQueue[tail]] >= a[i]) tail--;
        MonotoneQueue[++tail] = i;
        while (MonotoneQueue[head] <= i - k) head++;
        if (i >= k - 1)ansMin[i] = a[MonotoneQueue[head]];
    }
    head = 1, tail = 0;
    for (int i = 0; i < n; i++) {
        while (head <= tail && a[MonotoneQueue[tail]] <= a[i]) tail--;
        MonotoneQueue[++tail] = i;
        while (MonotoneQueue[head] <= i - k) head++;
        if (i >= k - 1)ansMax[i] = a[MonotoneQueue[head]];
    }
    for (int i = k - 1; i < n; i++) printf("%d ", ansMin[i]);
    puts("");
    for (int i = k - 1; i < n; i++) printf("%d ", ansMax[i]);
    puts("");
    return 0;
}