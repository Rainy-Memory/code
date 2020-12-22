#include <iostream>

using namespace std;

int m, n;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
const int maxn = 110;
//swing:0, red:1, blue:2
int map[maxn][maxn] = {0};
bool judge[maxn][maxn]={false};
int min_cost[maxn][maxn] = {0};

void dfs(int x0, int y0, int cost, bool can_change) {
    if (min_cost[x0][y0] == -1 || min_cost[x0][y0] > cost) {
        min_cost[x0][y0] = cost;
        for (int i = 0; i < 3; i++) {
            int x = x0 + dx[i], y = y0 + dy[i];
            if (x >= 0 && x < m && y >= 0 && y < m) {
                if(map[x][y]==0){
                    if(can_change){
                        map[x][y]=map[x0][y0];
                        judge[x][y]=true;
                        dfs(x,y,cost+2,false);
                        map[x][y]=0;
                    }
                }
                else {
                    if(map[x][y]==map[x0][y0]){
                        dfs(x,y,cost,true);
                    }
                    else {
                        dfs(x,y,cost+1,true);
                    }
                }
            }
        }
    }
}


int main() {
    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        int x0, y0, c0;
        cin >> x0 >> y0 >> c0;
        map[x0 - 1][y0 - 1] = c0 + 1;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            min_cost[i][j] = -1;
        }
    }
    dfs(0, 0, 0, true);
    cout << min_cost[m - 1][m - 1] << endl;
    return 0;
}