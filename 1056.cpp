#include<iostream>
#include <vector>
#include <queue>
#include <map>
#include <cstring>
using namespace std;
const int maxn = 1e6;
long long room[maxn] = { 0 };
int min_dis[maxn] = { 0 };
int n;
//vector<int> adjacent_room[maxn];
map<int,vector<int>> adjacent_room;
//int portal_num[maxn] = { 0 };

struct bfs {
    int distance = 0;
    int position = 0;
};


int main() {
    cin >> n;
    memset(min_dis, -1, sizeof(min_dis));
    /*
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        num += 1e6;
        room[i] = num;
        for (auto j : portal[num]) {
            adjacent_room[i].push_back(j);
            adjacent_room[j].push_back(i);
        }
        portal[num].push_back(i);
    }
    */
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        room[i] = num;
        adjacent_room[num].push_back(i);
    }



    queue<bfs> q;
    bfs start;
    q.push(start);
    min_dis[0] = 0;
    while (!q.empty()) {
        int distance0 = q.front().distance, position0 = q.front().position;
        //min_dis[position0] = distance0;
        q.pop();
        distance0++;
        //bool judge_bfs = true;
        while (true) {
            bfs temp;


            if (position0 == 0) {


                //right
                temp.position = position0 + 1;
                temp.distance = distance0;
                if (min_dis[temp.position] == -1 || min_dis[temp.position] > temp.distance) {
                    q.push(temp);
                    min_dis[temp.position] = temp.distance;
                }

                //portal
                for (auto i : adjacent_room[room[position0]]) {
                    if (i != position0 + 1) {
                        temp.position = i;
                        temp.distance = distance0;
                        if (min_dis[temp.position] == -1 || min_dis[temp.position] > temp.distance) {
                            q.push(temp);
                            min_dis[temp.position] = temp.distance;
                        }
                    }
                }
                adjacent_room[room[position0]].clear();

                break;

            }
            else if (position0 == n - 1) {


                //left
                temp.position = position0 - 1;
                temp.distance = distance0;
                if (min_dis[temp.position] == -1 || min_dis[temp.position] > temp.distance) {
                    q.push(temp);
                    min_dis[temp.position] = temp.distance;
                }

                //portal
                for (auto i : adjacent_room[room[position0]]) {
                    if (i != position0 - 1) {
                        temp.position = i;
                        temp.distance = distance0;
                        if (min_dis[temp.position] == -1 || min_dis[temp.position] > temp.distance) {
                            q.push(temp);
                            min_dis[temp.position] = temp.distance;
                        }
                    }
                }
                adjacent_room[room[position0]].clear();

                break;


            }
            else {

                //left
                temp.position = position0 - 1;
                temp.distance = distance0;
                if (min_dis[temp.position] == -1 || min_dis[temp.position] > temp.distance) {
                    q.push(temp);
                    min_dis[temp.position] = temp.distance;
                }

                //right
                temp.position = position0 + 1;
                temp.distance = distance0;
                if (min_dis[temp.position] == -1 || min_dis[temp.position] > temp.distance) {
                    q.push(temp);
                    min_dis[temp.position] = temp.distance;
                }

                //portal
                for (auto i : adjacent_room[room[position0]]) {
                    if ((i != position0 + 1) && (i != position0 - 1)) {
                        temp.position = i;
                        temp.distance = distance0;
                        if (min_dis[temp.position] == -1 || min_dis[temp.position] > temp.distance) {
                            q.push(temp);
                            min_dis[temp.position] = temp.distance;
                        }
                    }
                }
                adjacent_room[room[position0]].clear();


                break;


            }

        }
    }
    cout << min_dis[n - 1] << endl;

    return 0;
}