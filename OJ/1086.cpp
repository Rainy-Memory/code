//
// Created by Rainy Memory on 2021/3/14.
//

#include <cstdio>

#define MAXN 1000005

int n, top = 0, max = -1;
int h[MAXN] = {0}, v[MAXN] = {0}, MonotoneStack[MAXN] = {0}, ans[MAXN] = {0};

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &h[i], &v[i]);
        while (top > 0 && h[MonotoneStack[top]] < h[i]) ans[i] += v[MonotoneStack[top--]];
        if (top > 0) ans[MonotoneStack[top]] += v[i];
        MonotoneStack[++top] = i;
    }
    for (int i = 0; i < n; i++) {
        if (max < ans[i]) max = ans[i];
    }
    printf("%d\n", max);
    return 0;
}