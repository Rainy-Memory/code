//
// Created by Rainy Memory on 2021/5/29.
//

#include <iostream>

using namespace std;
#define maxn 107
typedef unsigned long long ll;
ll value[maxn][maxn];
ll map[maxn][maxn][3];
int dx[4] {0, 0, 1, -1};
int dy[4] {1, -1, 0, 0};
struct bfs_t {
    int x;
    int y;
    int step;
    ll cost;
};

template<class T>
class queue {
private:
    class node {
    public:
        node *pre = nullptr;
        node *next = nullptr;
        T value;
    };

    node *head = nullptr;
    node *tail = nullptr;
    int len = 0;

public:
    queue() {
        head = new node {};
        tail = new node {};
        head->next = tail, tail->pre = head;
    }

    ~queue() {
        node *temp = head;
        while (head != nullptr) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void push(const T &o) {
        node *newNode = new node {tail->pre, tail, o};
        tail->pre->next = newNode;
        tail->pre = newNode;
        len++;
    }

    T pop() {
        node *temp = head->next;
        T res {temp->value};
        head->next->next->pre = head;
        head->next = head->next->next;
        delete temp;
        len--;
        return res;
    }

    bool empty() const {
        return len == 0;
    }
};

ll bfs(int n, ll t) {
    queue<bfs_t> q;
    q.push(bfs_t {1, 1, 0, 0});
    map[1][1][0] = 0;
    while (!q.empty()) {
        bfs_t now = q.pop();
        for (int i = 0; i < 4; i++) {
            int x = now.x + dx[i], y = now.y + dy[i], step = now.step + 1;
            if (!(x >= 1 && x <= n && y >= 1 && y <= n))continue;
            ll cost = now.cost + t + (step % 3 == 0 ? value[x][y] : 0);
            if (map[x][y][step % 3] > cost) {
                map[x][y][step % 3] = cost;
                q.push(bfs_t {x, y, step, cost});
            }
        }
    }
    return min(map[n][n][0], min(map[n][n][1], map[n][n][2]));
}

int main() {
    int n;
    ll t;
    cin >> n >> t;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> value[i][j], map[i][j][0] = map[i][j][1] = map[i][j][2] = 0xffffffffffffffff;
    cout << bfs(n, t) << endl;
    return 0;
}