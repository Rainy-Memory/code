//
// Created by Rainy Memory on 2021/5/11.
//

#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::ios;

#define maxn 200007

struct mouse {
    long long score;
    int might;
    int number;
    
    bool operator<(const mouse &o) const {
        return score != o.score ? score > o.score : number < o.number;
    }
    
    bool operator>(const mouse &o) const {
        return score != o.score ? score < o.score : number > o.number;
    }
} mice[maxn], temp[maxn];

void merge_sort(int l, int r) {
    if (r - l <= 1)return;
    int m = l + ((r - l) >> 1);
    merge_sort(l, m);
    merge_sort(m, r);
    int p = l, q = m, now = l;
    while (now < r) {
        if (p >= m || (q < r && mice[p] > mice[q]))temp[now++] = mice[q++];
        else temp[now++] = mice[p++];
    }
    for (int i = l; i < r; i++)mice[i] = temp[i];
}

int main() {
    ios::sync_with_stdio(false);
    int n, r;
    cin >> n >> r;
    n <<= 1;
    for (int i = 1; i <= n; i++)cin >> mice[i].score, mice[i].number = i;
    for (int i = 1; i <= n; i++)cin >> mice[i].might;
    merge_sort(1, n + 1);
    while (r--) {
        for (int i = 1; i < n; i += 2) {
            if (mice[i].might < mice[i + 1].might)mice[i + 1].score += 2;
            else if (mice[i].might > mice[i + 1].might)mice[i].score += 2;
            else mice[i].score++, mice[i + 1].score++;
        }
        merge_sort(1, n + 1);
    }
    for (int i = 1; i <= n; i++)cout << mice[i].number << " ";
    cout << endl;
    return 0;
}