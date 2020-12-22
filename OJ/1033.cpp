//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>

using namespace std;
int matrix[10][10] = {0};
bool chosen[10] = {false};
int n, determine = 0;

int change_invertion(int k) {
    int s = 0;
    for (int i = k + 1; i < n; i++) {
        if (chosen[i])s++;
    }
    if (s % 2 == 0)return 1;
    else return -1;
}

int dfs(int row, int inversion, int product) {
    if (row != n - 1) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (!chosen[i]) {
                chosen[i] = true;
                inversion *= change_invertion(i);
                int temp_product = dfs(row + 1, 1, matrix[row][i]);
                sum += product * inversion * temp_product;
                chosen[i] = false;
                inversion *= change_invertion(i);
            }
        }
        return sum;
    } else {
        int k = 10;
        for (int i = 0; i < n; i++) {
            if (!chosen[i]) {
                k = i;
                break;
            }
        }
        inversion *= change_invertion(k);
        product *= (matrix[row][k] * inversion);
        return product;
    }
}


int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    if (n == 1)cout << matrix[0][0] << endl;
    else {
        for (int i = 0; i < n; i++) {
            chosen[i] = true;
            determine += dfs(1, 1, matrix[0][i]);
            chosen[i] = false;
        }
        cout << determine << endl;
    }
    return 0;
}