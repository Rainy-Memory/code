//
// Created by Rainy Memory on 2021/4/12.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

#define maxn 1007
#define maxm 100007
#define mod 68861641
#define base1 32
#define base2 31
int n, m, head = 0, tail = 0, cnt = 0;
int visited[mod] = {0};
bool exist[mod] = {false};
string target[maxn];
string article[maxm];
long long hash_article[maxm];
int max_paragraph[maxn] = {0};

long long hash_str(const string &o) {
    long long h1 = 0, h2 = 0, now = 1;
    for (char i : o) {
        h1 += (i - 'a') * now;
        h1 %= mod;
        now *= base1;
    }
    for (char i : o) {
        h2 += (i - 'a') * now;
        h2 %= mod;
        now *= base2;
    }
    long long h = ((h1 << 32) | h2) % mod;
    if (h < 0)h += mod;
    return h;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> target[i];
        exist[hash_str(target[i])] = true;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> article[i];
        hash_article[i] = hash_str(article[i]);
    }
    while (tail < m) {
        if (exist[hash_article[tail]]) {
            if (head == tail || visited[hash_article[tail]] == 0)cnt++;
            visited[hash_article[tail++]]++;
            while (head < tail && (!exist[hash_article[head]] || visited[hash_article[head]] > 1))visited[hash_article[head++]]--;
            if (max_paragraph[cnt] == 0 || max_paragraph[cnt] > tail - head)max_paragraph[cnt] = tail - head;
        }
        else tail++;
    }
    cout << cnt << endl;
    cout << max_paragraph[cnt] << endl;
    return 0;
}