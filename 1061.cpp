//
// Created by Rainy Memory on 2020/11/29.
//

#include <iostream>

using namespace std;

int t[110] = {0}, n;
int f_up[110] = {0}, f_down[110] = {0};

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }
    //0 ~ n - 1 -> find max up array length l1
    //0 ~ n - 1 -> find max down array length l2
    //find max f_up[i] + f_down[i]
    
    //find l1
    for (int i = 0; i < n; i++) {
        int temp_len = 1;
        for (int j = 0; j < i; j++) {
            if (t[j] < t[i]) {
                if (temp_len < (f_up[j] + 1))temp_len = (f_up[j] + 1);
            }
        }
        f_up[i] = temp_len;
    }
    
    //find l2
    for (int i = n - 1; i >= 0; i--) {
        int temp_len = 1;
        for (int j = n - 1; j > i; j--) {
            if (t[j] < t[i]) {
                if (temp_len < (f_down[j] + 1))temp_len = (f_down[j] + 1);
            }
        }
        f_down[i] = temp_len;
    }
    
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (result < (f_up[i] + f_down[i] - 1))result = (f_up[i] + f_down[i] - 1);
    }
    
    
    cout << n - result << endl;
    
    return 0;
}