//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
#include <string.h>
using namespace std;
int chain[300000] = { 0 }, save[300000] = { 0 };
int n, k;
bool judge(int maxnum) {
    int head = 0;
    save[0] = 1;
    while (true) {
        if (chain[head] <= maxnum) {
            int tail = (head + 1) % n, count = 1;
            save[tail] = 1;
            while (true) {
                if (chain[tail] <= maxnum) {
                    count++;
                    tail++;
                    tail %= n;
                    save[tail] = 1;
                }
                else {
                    if (count >= k) {
                        memset(save, 0, sizeof(save));
                        return true;
                    }
                    else {
                        head = tail + 1;
                        if ((head / n) >= 1) {
                            memset(save, 0, sizeof(save));
                            return false;
                        }
                        head %= n;
                        if (save[head] == 1) {
                            memset(save, 0, sizeof(save));
                            return false;
                        }
                        save[head] = 1;
                    }
                    break;
                }
            }
        }
        else {
            head++;
            if ((head / n) >= 1) {
                memset(save, 0, sizeof(save));
                return false;
            }
            head %= n;
            if (save[head] == 1) {
                memset(save, 0, sizeof(save));
                return false;
            }
            save[head] = 1;
        }
    }
}
int main() {
    int s = 0, min = 1000000000, max = 0;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        scanf("%d", &chain[i]);
        if (chain[i] <= min)min = chain[i];
        if (chain[i] >= max)max = chain[i];
    }
    int result = 0;
    while (s == 0) {
        int mid = (max + min) / 2;
        if (max - min >= 5) {
            if (judge(mid))max = mid;
            else min = mid;
        }
        else {
            for (int i = min; i <= max; i++) {
                if (judge(i)) {
                    result = i;
                    s++;
                    break;
                }
            }
        }
    }
    cout << result << endl;
    return 0;
}