//
// Created by Rainy Memory on 2021/4/13.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

#define maxn 200007

struct BG {
    int B;
    int G;
    int diff;
    
    BG(int b, int g, int b_a, int g_a) : B(b), G(g), diff(b_a > g_a ? b_a - g_a : g_a - b_a) {}
    
    bool operator<(BG other) const {
        if (diff != other.diff)return diff > other.diff;
        else return min(B, G) > min(other.B, other.G);
    }
};

int n, b_cnt = 0, g_cnt = 0, pair_cnt, min_index, max_index, l, r;
bool flag_l, flag_r;
char latin_queue[maxn];
int ability[maxn];
bool out[maxn] = {false};
priority_queue<BG> pq;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    cin >> (latin_queue + 1);
    for (int i = 1; i <= n; i++) {
        cin >> ability[i];
        if (latin_queue[i] == 'B')b_cnt++;
        else g_cnt++;
    }
    cout << (pair_cnt = min(b_cnt, g_cnt)) << endl;
    for (int i = 1; i < n; i++) {
        if (latin_queue[i] != latin_queue[i + 1]) {
            if (latin_queue[i] == 'B')pq.push(BG(i, i + 1, ability[i], ability[i + 1]));
            else pq.push(BG(i + 1, i, ability[i + 1], ability[i]));
        }
    }
    while (pair_cnt > 0) {
        while (!pq.empty() && (out[pq.top().B] || out[pq.top().G]))pq.pop();
        BG temp = pq.top();
        pq.pop(), pair_cnt--;
        min_index = min(temp.B, temp.G), max_index = max(temp.B, temp.G);
        out[temp.B] = out[temp.G] = true;
        flag_l = flag_r = false;
        for (int i = min_index; i > 0; i--) {
            if (!out[i]) {
                l = i, flag_l = true;
                break;
            }
        }
        for (int i = max_index; i <= n; i++) {
            if (!out[i]) {
                r = i, flag_r = true;
                break;
            }
        }
        if (flag_l && flag_r && latin_queue[l] != latin_queue[r]) {
            if (latin_queue[l] == 'B')pq.push(BG(l, r, ability[l], ability[r]));
            else pq.push(BG(r, l, ability[r], ability[l]));
        }
        cout << min_index << " " << max_index << endl;
    }
    return 0;
}