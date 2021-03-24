//
// Created by Rainy Memory on 2021/3/18.
//

#include <cstdio>

#define maxn 3005

int n, m, top = 0, result = -1;
int MonotoneStack[maxn] = {0};
int matrix[maxn][maxn] = {0};
int alpha[maxn] = {0};

inline void read(int &o) {
    char c = getchar();
    while (c > '9' || c < '0')c = getchar();
    o = 0;
    while (c <= '9' && c >= '0')o = (o << 3) + (o << 1) + c - '0', c = getchar();
}

int main() {
    read(n), read(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            read(matrix[i][j]);
        }
    }
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n - 1; i++) {
            if (matrix[i + 1][j] > 0)matrix[i + 1][j] = matrix[i][j] + 1;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            bool flag = false;
            while (top > 0 && MonotoneStack[top - 1] > matrix[i][j]) {
                int temp = MonotoneStack[top - 1] * (j - alpha[top - 1]);
                if (result < temp)result = temp;
                flag = true;
                top--;
            }
            if (matrix[i][j] != 0) {
                MonotoneStack[top] = matrix[i][j];
                if(!flag)alpha[top] = j;
                top++;
            }
        }
        while (top > 0) {
            int temp = MonotoneStack[top - 1] * (m - alpha[top - 1]);
            if (result < temp)result = temp;
            top--;
        }
    }
    printf("%d\n", result);
    return 0;
}