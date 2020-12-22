//
// Created by Rainy Memory on 2020/11/29.
//

#include <iostream>

using namespace std;
int n, m, use_row = 0;
int f[1005][2] = {0};
int v = 0, p = 0, w = 0;

int max_num(const int &a, const int &b) {
    return (a > b ? a : b);
}

int reverse(int a) {
    if (a == 0)return 1;
    if (a == 1)return 0;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> p >> w >> v;
        int divide_of_p[20] = {0};
        int bi_count = 1, digit_bi = 0;
        for (int j = 1; j <= 20; j++) {
            //digit_bi++;
            if (p >= bi_count) {
                p -= bi_count;
                divide_of_p[j] = bi_count;
                bi_count *= 2;
            }
            else {
                divide_of_p[j] = p;
                digit_bi = (p == 0) ? j - 1 : j;
                break;
            }
        }
        for (int j = 1; j <= digit_bi; j++) {
            //if(divide_of_p[j]==0)break;
            int weight = divide_of_p[j] * w;
            int value = divide_of_p[j] * v;
            int store_row = reverse(use_row);
            for (int k = 0; k <= m; k++) {
                f[k][use_row] = (k >= weight) ? max_num(f[k][store_row], f[k - weight][store_row] + value) : f[k][store_row];
            }
            use_row = store_row;
        }
    }
    int final_store_row = reverse(use_row);
    cout << f[m][final_store_row] << endl;
    
    return 0;
}