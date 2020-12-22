#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int n, k, result = -1;
const int maxn = 1e5 + 1e2;
struct road {
    int destination;
    int length;
};
struct bfs {
    int position = 0;
    int distance = 0;
};
vector<road> adjacent[maxn];
bool is_store[maxn] = {false};
vector<int> store;
int max_distance[maxn];

void initialize() {
    memset(max_distance, -1, sizeof(max_distance));
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v, l;
        cin >> u >> v >> l;
        road temp;
        temp.length = l;
        temp.destination = u;
        adjacent[v].push_back(temp);
        temp.destination = v;
        adjacent[u].push_back(temp);
    }
    for (int i = 0; i < k; i++) {
        int a;
        cin >> a;
        is_store[a] = true;
        store.push_back(a);
    }
}

void scan(int store_No) {
    bool pass[maxn] = {false};
    queue<bfs> q;
    bfs start;
    start.position = store_No;
    q.push(start);
    pass[store_No] = true;
    while (!q.empty()) {
        int dis = q.front().distance, pos = q.front().position;
        if (max_distance[pos] == -1 || max_distance[pos] < dis)max_distance[pos] = dis;
        q.pop();
        bfs temp;
        for (auto i:adjacent[pos]) {
            if (!pass[i.destination]) {
                temp.distance = i.length + dis;
                temp.position = i.destination;
                q.push(temp);
                pass[i.destination] = true;
            }
        }
    }
}

void todo() {
    for (int i = 0; i < k; i++) {
        scan(store[i]);
    }
}

void find_result() {
    for (int i = 0; i < n; i++) {
        if (result == -1 || result > max_distance[i])result = max_distance[i];
    }
    int result_No;
    for (int i = 0; i < n; i++) {
        if (max_distance[i] == result) {
            result_No = i;
            break;
        }
    }
    cout << result_No << " " << result << endl;
}


int main() {
    initialize();
    todo();
    find_result();
    return 0;
}
