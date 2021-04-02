//
// Created by Rainy Memory on 2021/3/29.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

namespace RainyMemory {
    template<class T>
    class vector {
    private:
        T *store = nullptr;
        int capacity = 10;
        int tail = 0;
        
        void double_space() {
            T *temp = new T[capacity <<= 1];
            for (int i = 0; i < tail; i++)temp[i] = store[i];
            delete[]store;
            store = temp;
        }
    
    public:
        vector() {
            store = new T[capacity];
        }
        
        ~vector() {
            delete[]store;
        }
        
        T &operator[](int index) {
            return store[index];
        }
        
        const T &operator[](int index) const {
            return store[index];
        }
        
        void push_back(const T &o) {
            store[tail++] = o;
            if (tail == capacity)double_space();
        }
        
        int size() const {
            return tail;
        }
    };
}

using RainyMemory::vector;

using namespace std;

template<class T>
inline void read(T &o) {
    char c = getchar();
    while (c < '0' || c > '9')c = getchar();
    o = 0;
    while (c >= '0' && c <= '9')o = (o << 3) + (o << 1) + c - '0', c = getchar();
}

#define maxn 100007
int n, k;
vector<int> adjacent[maxn];
vector<int> son_node[maxn];
vector<int> res;
int lower_point[maxn] = {0};
bool chosen[maxn] = {false};

void initialize_tree(int father) {
    for (int i = 0; i < adjacent[father].size(); i++) {
        if (!chosen[adjacent[father][i]]) {
            son_node[father].push_back(adjacent[father][i]);
            chosen[adjacent[father][i]] = true;
            initialize_tree(adjacent[father][i]);
        }
    }
}

int calculate_lower_point(int father) {
    int sum = 1;
    for (int i = 0; i < son_node[father].size(); i++) {
        int low = calculate_lower_point(son_node[father][i]);
        sum += low;
    }
    lower_point[father] = sum;
    return sum;
}

int main() {
    read(n);
    k = n >> 1;
    for (int i = 1; i < n; i++) {
        int n1, n2;
        read(n1), read(n2);
        adjacent[n1].push_back(n2);
        adjacent[n2].push_back(n1);
    }
    chosen[1] = true;
    initialize_tree(1);
    calculate_lower_point(1);
    int s = 0;
    for (int i = n; i >= 1; i--) {
        bool judge = true;
        for (int j = 0; j < son_node[i].size(); j++) {
            if (lower_point[son_node[i][j]] > k)judge = false;
        }
        if ((n - lower_point[i]) > k)judge = false;
        if (judge) {
            s++;
            res.push_back(i);
        }
    }
    for (int i = res.size() - 1; i >= 0; i--)printf("%d\n", res[i]);
    return 0;
}