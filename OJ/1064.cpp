//
// Created by Rainy Memory on 2020/12/2.
//
#include <iostream>

using namespace std;

int n, m, k;
const int maxn = 420, maxk = 1e6 + 1e2;
int map[maxn][maxn] = {0};
int prefix[maxn][maxn] = {0};
int cnt[maxk] = {0};

int dif_modk(int a, int b) {
    return ((a >= b) ? (a - b) : (a - b + k));
}

int main() {
    long long result = 0;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> map[i][j];
            prefix[i][j] = (prefix[i][j - 1] + prefix[i - 1][j] - prefix[i - 1][j - 1] + map[i][j])%k;
            if(prefix[i][j]<0)prefix[i][j]+=k;
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = i; j <= m; j++) {
            for (int l = 0; l <= n; l++) {
                //left:i right:j up:1 down:l
                int now_dif = dif_modk(prefix[l][j], prefix[l][i - 1]);
                result += cnt[now_dif];
                cnt[now_dif]++;
            }
            for (int l = 0; l <= n; l++) {
                //left:i right:j up:1 down:l
                int now_dif = dif_modk(prefix[l][j], prefix[l][i - 1]);
                cnt[now_dif]--;
            }
        }
    }
    cout << result << endl;
    return 0;
}