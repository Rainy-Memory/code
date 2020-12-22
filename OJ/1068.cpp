//
// Created by Rainy Memory on 2020/11/30.
//

#include <iostream>

using namespace std;
const int maxn = 55;
int m, n;
int dx1[4] = {0, -1, -1, 0};
int dx2[4] = {-1, 0, -1, 0};
int value[maxn][maxn] = {0};
int p[maxn][maxn][maxn + maxn] = {0};

int main() {
    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> value[i][j];
        }
    }
    p[1][1][2] = 0;
    for (int k = 3; k <= m + n; k++) {
        for (int i = 1; i <= m&&i<k; i++) {
            for (int j = i + 1; j <= m&&j<k; j++) {
                //if(i+j>k)break;
                int temp = 0;
                for (int l = 0; l < 4; l++) {
                    if ((i + dx1[l] >= 1) && (i + dx1[l] <= m) && (j + dx2[l] >= 1) && (j + dx2[l] <= m)) {
                        if (temp < p[i + dx1[l]][j + dx2[l]][k - 1])temp = p[i + dx1[l]][j + dx2[l]][k - 1];
                    }
                }
                p[i][j][k] = temp + value[i][k - i] + value[j][k - j];
            }
        }
    }
    int result = p[m - 1][m][m + n - 1];
    cout << result << endl;
    return 0;
}