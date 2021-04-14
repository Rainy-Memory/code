//
// Created by Rainy Memory on 2021/4/14.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

#define maxn 300007
#define maxm 1007
int n, m;

struct node {
    long long w = 0;
    long long sum = 0;
    long long depth = 0;
    
    node(long long o1, long long o2, long long o3) : w(o1), sum(o2), depth(o3) {}
    
    explicit node(long long o) : w(o) {}
    
    node() = default;
    
    bool operator<(node o) const {
        return w > o.w;
    }
};

int main() {
    ios::sync_with_stdio(false);
    priority_queue<node> heap;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        long long temp;
        cin >> temp;
        heap.push(node(temp));
    }
    if ((n - 1) % (m - 1) != 0) {
        for (int i = 0; i < ((m - 1) - (n - 1) % (m - 1)); i++)heap.push(node());
    }
    while (heap.size() > 1) {
        node new_node, temp;
        for (int i = 0; i < m; i++) {
            temp = heap.top(), heap.pop();
            new_node.w += temp.w;
            new_node.sum += temp.w + temp.sum;
            if (new_node.depth < temp.depth + 1)new_node.depth = temp.depth + 1;
        }
        heap.push(new_node);
    }
    cout << heap.top().sum << endl;
    return 0;
}