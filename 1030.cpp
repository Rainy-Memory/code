//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
#include <cstring>
#include <utility>
#include <iomanip>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int m, n;
const int maxn = 510;
int map_[maxn][maxn] = { 0 };
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };


struct poi {
    int x = 0;
    int y = 0;
};

vector<poi> v;
int i_ = 0;
int j_ = 0;


poi find_next() {
    for (int i = i_; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map_[i][j] == 0) {
                poi temp;
                temp.x = i;
                temp.y = j;
                i_ = i;
                j_ = j;
                return temp;
            }
        }
    }
    poi temp;
    temp.x = -1;
    temp.y = -1;
    return temp;
}


int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> map_[i][j];
        }
    }
    int count = 0;
    queue<poi> q;
    while (true) {
        poi start = find_next();
        if (start.x == -1 && start.y == -1)break;
        q.push(start);
        map_[start.x][start.y] = -1;
        while (!q.empty()) {
            for (int i = 0; i < 4; i++) {
                int x = q.front().x + dx[i];
                int y = q.front().y + dy[i];
                if (x >= 0 && x < n && y >= 0 && y < m) {
                    if (map_[x][y] == 0) {
                        poi temp;
                        temp.x = x;
                        temp.y = y;
                        q.push(temp);
                        map_[x][y] = -1;
                    }
                }
            }
            q.pop();
        }
        count++;
    }
    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << map_[i][j] << " ";
        }
        cout << endl;
    }
    */
    cout << count << endl;
    
    
    
    
    return 0;
}