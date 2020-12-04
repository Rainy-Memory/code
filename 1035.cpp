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
char map_[1000][1000];
int bar[1000][1000] = { 0 };
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int if_pass[1000][1000] = { 0 };
int umbrella1[10000000];
int umbrella2[10000000];


struct dataT {
    int x = 0;
    int y = 0;
    int distance = 0;
};


void min_dist(int x_, int y_, int z) {
    queue<dataT> q;
    dataT start;
    start.x = x_;
    start.y = y_;
    if_pass[x_][y_] = 1;
    q.push(start);
    while (!q.empty()) {
        int x0 = q.front().x;
        int y0 = q.front().y;
        int distance = q.front().distance;
        int count = 0;
        for (int i = 0; i < 4; i++) {
            int x = x0 + dx[i];
            int y = y0 + dy[i];
            if (x >= 0 && x < m && y >= 0 && y < n) {
                if (if_pass[x][y] == 0) {
                    if (map_[x][y] == 'B') {
                        int distan = distance + 1;
                        int num = bar[x][y];
                        if (z == 1) {
                            if (umbrella1[num] == -1 || umbrella1[num] > distan)umbrella1[num] = distan;
                        }
                        else if (z == 2) {
                            if (umbrella2[num] == -1 || umbrella2[num] > distan)umbrella2[num] = distan;
                        }
                        dataT next;
                        next.x = x;
                        next.y = y;
                        next.distance = distance + 1;
                        q.push(next);
                    }
                    else if (map_[x][y] != '#') {
                        dataT next;
                        next.x = x;
                        next.y = y;
                        next.distance = distance + 1;
                        q.push(next);
                    }
                    if_pass[x][y] = 1;
                }
                
                
                
            }
            
        }
        q.pop();
        
        
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if_pass[i][j] = 0;
        }
    }
    return;
}



int main() {
    cin >> n >> m;
    int startx, endx, starty, endy, num_of_umb = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map_[i][j];
            if (map_[i][j] == 'H') {
                startx = i;
                starty = j;
            }
            else if (map_[i][j] == 'S') {
                endx = i;
                endy = j;
            }
            else if (map_[i][j] == 'B') {
                num_of_umb++;
                bar[i][j] += num_of_umb;
            }
        }
    }
    memset(umbrella1, -1, sizeof(umbrella1));
    memset(umbrella2, -1, sizeof(umbrella2));
    min_dist(startx, starty, 1);
    min_dist(endx, endy, 2);
    int result = -1;
    for (int i = 1; i <= num_of_umb; i++) {
        int dist0 = umbrella1[i] + umbrella2[i];
        if (umbrella1[i] != -1 && umbrella2[i] != -1) {
            if (result == -1) result = dist0;
            else if (result > dist0)result = dist0;
        }
    }
    cout << result << endl;
    return 0;
}