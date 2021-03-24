//
// Created by Rainy Memory on 2021/3/14.
//

#include <cstdio>

int essay[1005] = {0};
int queue[105] = {0};
bool stored[1005] = {false};
int m, n, used = 0, head = 0, tail = 0, ans = 0;

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &essay[i]);
        if (!stored[essay[i]]) {
            ans++;
            if (used < m)used++;
            else stored[queue[head++]] = false;
            stored[essay[i]] = true;
            queue[tail++] = essay[i];
        }
    }
    printf("%d\n", ans);
    return 0;
}