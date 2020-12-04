//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
#include <cstring>
#include <utility>
#include <queue>
using namespace std;

struct save {
    int row = 0;
    int column = 0;
    int altitude = 0;
    bool flag = false;
};

save map[500][500];
int if_pass[500][500] = { 0 };
int m, n, num_of_flag = 0;

int dif(int a, int b) {
    int c = (a > b ? a - b : b - a);
    return c;
}

bool judge(int alti) {
    int count = 1, row0, column0, s = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j].flag) {
                row0 = i;
                column0 = j;
                s++;
                break;
            }
        }
        if (s == 1)break;
    }
    queue<save> q;
    q.push(map[row0][column0]);
    if_pass[row0][column0] = 1;
    while (!q.empty()) {
        int row = q.front().row, column = q.front().column, s0 = 0;
        int altitude = map[row][column].altitude;
        if (row != 0) {
            if (dif(map[row - 1][column].altitude, altitude) <= alti) {
                if (if_pass[row - 1][column] == 0) {
                    q.push(map[row - 1][column]);
                    if (map[row - 1][column].flag)count++;
                    //s0++;
                    if_pass[row - 1][column] = 1;
                }
            }
        }
        if (row != m - 1) {
            if (dif(map[row + 1][column].altitude, altitude) <= alti) {
                if (if_pass[row + 1][column] == 0) {
                    q.push(map[row + 1][column]);
                    if (map[row + 1][column].flag)count++;
                    //s0++;
                    if_pass[row + 1][column] = 1;
                }
            }
        }
        if (column != 0) {
            if (dif(map[row][column - 1].altitude, altitude) <= alti) {
                if (if_pass[row][column - 1] == 0) {
                    q.push(map[row][column - 1]);
                    if (map[row][column - 1].flag)count++;
                    //s0++;
                    if_pass[row][column - 1] = 1;
                }
            }
        }
        if (column != n - 1) {
            if (dif(map[row][column + 1].altitude, altitude) <= alti) {
                if (if_pass[row][column + 1] == 0) {
                    q.push(map[row][column + 1]);
                    if (map[row][column + 1].flag)count++;
                    //s0++;
                    if_pass[row][column + 1] = 1;
                }
            }
        }
        q.pop();
    }
    memset(if_pass, 0, sizeof(if_pass));
    if (count == num_of_flag)return true;
    else return false;
}



int main() {
    int max_alti = 0, min_alti = 0;
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j].altitude;
            map[i][j].row = i;
            map[i][j].column = j;
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int flag;
            cin >> flag;
            if (flag == 0)map[i][j].flag = false;
            else {
                map[i][j].flag = true;
                num_of_flag++;
            }
        }
    }
    max_alti = map[0][0].altitude;
    min_alti = map[0][0].altitude;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j].altitude > max_alti)max_alti = map[i][j].altitude;
            if (map[i][j].altitude < min_alti)min_alti = map[i][j].altitude;
        }
    }
    
    
    int count = 0, max = max_alti - min_alti, min = 0;
    //if (judge(4))cout << "4" << endl;
    //if (judge(3))cout << "3" << endl;
    //if (judge(2))cout << "2" << endl;
    //if (judge(1))cout << "1" << endl;
    //if (judge(0))cout << "0" << endl;
    
    while (true) {
        int mid = (max + min) / 2;
        if (max - min >= 5) {
            if (judge(mid))max = mid;
            else min = mid;
        }
        else {
            for (int i = min; i <= max; i++) {
                if (judge(i)) {
                    cout << i << endl;
                    return 0;
                }
            }
        }
    }
    
    
    
    return 0;
}