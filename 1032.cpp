//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
#include <queue>

using namespace std;

const int maxn = 310;
int n, m;
int map[maxn][maxn] = {0};
int pass[maxn][maxn][2] = {0};
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
struct point {
    int x = 0;
    int y = 0;
    int distance = 0;
    int power = 6;
};
queue<point> q;

void insert(int x, int y, int distance, int power) {
    point temp;
    temp.x = x;
    temp.y = y;
    temp.distance = distance;
    temp.power = power;
    q.push(temp);
}

int main() {
    int startx, starty, min = -1;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
            if (map[i][j] == 2) {
                startx = i;
                starty = j;
            }
        }
    }
    
    point start;
    start.x = startx;
    start.y = starty;
    q.push(start);
    pass[startx][starty][0] = 1;
    pass[startx][starty][1] = 6;
    while (!q.empty()) {
        int x0 = q.front().x, y0 = q.front().y, distance = q.front().distance, power = q.front().power;
        //if(map[x0][y0]!=0){pass[x0][y0][0] = 1;pass[x0][y0][1]}
        q.pop();
        power--;
        distance++;
        if (power > 0) {
            for (int i = 0; i < 4; i++) {
                int x = x0 + dx[i], y = y0 + dy[i];
                if (x >= 0 && x < n && y >= 0 && y < m) {
                    if (pass[x][y][0] == 0 || (pass[x][y][0] == 1 && pass[x][y][1] < power)) {
                        if(map[x][y]!=0){
                            pass[x][y][0] = 1;
                            pass[x][y][1] = power;
                            if (map[x][y] == 4) {
                                //power = 6;
                                pass[x][y][1] = 6;
                                insert(x, y, distance, 6);
                            } else if (map[x][y] == 3) {
                                if (min == -1 || min > distance)min = distance;
                            } else if (map[x][y] == 1 || map[x][y] == 2) {
                                insert(x, y, distance, power);
                            }
                        }
                    }
                }
            }
        }
    }
    
    cout << min << endl;
    return 0;
}