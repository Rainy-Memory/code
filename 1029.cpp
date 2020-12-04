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

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int map_[6][6];
int if_pass[6][6] = { 0 };
int lowcost = -1;

void dfs(int x, int y, int status, int cost, int endx, int endy) {
    if (x == endx && y == endy) {
        if (lowcost == -1) {
            lowcost = cost;
        }
        else if (lowcost > cost) {
            lowcost = cost;
        }
        //return cost;
    }
    else {
        for (int i = 0; i < 4; i++) {
            int x0 = x + dx[i];
            int y0 = y + dy[i];
            if (0 <= x0 && x0 < 6 && 0 <= y0 && y0 < 6 && if_pass[x0][y0] == 0) {
                int cost0 = map_[x0][y0] * status;
                int status0 = (cost0 % 4) + 1;
                cost0 += cost;
                if_pass[x0][y0] = 1;
                //int result0 = dfs(x0, y0, status0, cost0, endx, endy);
                dfs(x0, y0, status0, cost0, endx, endy);
                if_pass[x0][y0] = 0;
                //return result0;
            }
            
        }
    }
}


int main() {
    int n;
    cin >> n;
    for (int i0 = 0; i0 < n; i0++) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cin >> map_[i][j];
            }
        }
        int startx, starty, endx, endy, status = 1, cost = 0;
        cin >> startx >> starty >> endx >> endy;
        //int result = dfs(startx, starty, status, cost, endx, endy);
        dfs(startx, starty, status, cost, endx, endy);
        cout << lowcost << endl;
        lowcost = -1;
    }
    
    
    return 0;
}