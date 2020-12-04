//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
#include <cstring>
#include <utility>
#include <iomanip>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 2010;
int map[maxn][maxn][2] = { 0 };
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
struct dataT {
    int x = 1000;
    int y = 1000;
    int distance = 0;
};

int main() {
    int x, y, n, min = -1;
    cin >> x >> y >> n;
    x += 1000; y += 1000;
    map[x][y][0] = 2;
    for (int i = 0; i < n; i++) {
        int ai, bi;
        cin >> ai >> bi;
        ai += 1000; bi += 1000;
        map[ai][bi][0] = 1;
    }
    queue<dataT> q;
    dataT start;
    map[1000][1000][1] = 1;
    q.push(start);
    while (!q.empty()) {
        int x_ = q.front().x;
        int y_ = q.front().y;
        int dist = q.front().distance + 1;
        for (int i = 0; i < 4; i++) {
            int x0 = x_ + dx[i];
            int y0 = y_ + dy[i];
            if (x0 == x && y0 == y) {
                if (min == -1 || min > dist)min = dist;
            }
            else {
                if (x0 >= 480 && x0 < 1520 && y0 >= 480 && y0 <= 1520) {
                    if (map[x0][y0][0] != 1 && map[x0][y0][1] != 1) {
                        dataT temp;
                        temp.x = x0;
                        temp.y = y0;
                        temp.distance = dist;
                        map[x0][y0][1] = 1;
                        q.push(temp);
                    }
                    
                }
            }
        }
        q.pop();
        
        
        
    }
    cout << min << endl;
    
    
    
    
}