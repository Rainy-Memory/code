//
// Created by Rainy Memory on 2020/12/1.
//

#include <iostream>

using namespace std;

int n = 0;
const int maxn = 210;
int head[maxn] = {0}, tail[maxn] = {0};
int dp[maxn][maxn] = {0};
//dp[i][j] represent length = i & start from j


int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> head[i];
        head[i + n] = head[i];
        if (i != 1) {
            tail[i - 1] = head[i];
            tail[i - 1 + n] = tail[i - 1];
        }
        
    }
    tail[n] = head[1];
    tail[2 * n] = tail[n];
    
    //k:length l:left r:right
    for (int k = 1; k <= n; k++) {
        for (int l = 1; l <= 2 * n - k; l++) {
            int r = l + k - 1;
            //compound l~i & i+1~r
            for (int i = l; i < r; i++) {
                dp[l][r] = max(dp[l][r], dp[l][i] + dp[i + 1][r] + head[l] * tail[i] * tail[r]);
            }
        }
    }
    int result = -1;
    for (int i = 1; i <= n; i++) {
        result = max(result, dp[i][i + n - 1]);
    }
    cout << result << endl;
    return 0;
}