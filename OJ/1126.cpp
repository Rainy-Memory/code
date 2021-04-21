//
// Created by Rainy Memory on 2021/4/14.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

namespace RainyMemory {
    template<class T, int max_length, class Compare = std::less<T>>
    class priority_queue {
    private:
        Compare cmp;
        T sequence[max_length];
        int tail = 1;
    
    public:
        priority_queue() = default;
        
        void push(const T &o) {
            sequence[tail] = o;
            int index = tail++;
            while (cmp(sequence[index >> 1], sequence[index]) && index > 1)std::swap(sequence[index >> 1], sequence[index]), index >>= 1;
        }
        
        int size() const {
            return tail - 1;
        }
        
        const T &top() const {
            return sequence[1];
        }
        
        void pop() {
            sequence[1] = sequence[--tail];
            int now = 1, child;
            while ((now << 1) < tail) {
                child = (now << 1 | 1) < tail && cmp(sequence[now << 1], sequence[now << 1 | 1]) ? now << 1 | 1 : now << 1;
                if (cmp(sequence[now], sequence[child]))std::swap(sequence[now], sequence[child]), now = child;
                else break;
            }
        }
    };
}

using namespace std;

#define maxn 300007
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
    RainyMemory::priority_queue<node, maxn> heap;
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