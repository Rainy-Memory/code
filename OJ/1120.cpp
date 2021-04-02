//
// Created by RainyMemory on 2021/4/1.


#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

#define maxn 100007

class vector {
private:
    int *store;
    int capacity = 10;
    int tail = 0;
    
    void double_space() {
        int *temp = new int[capacity <<= 1];
        for (int i = 0; i < tail; i++)temp[i] = store[i];
        delete[]store;
        store = temp;
    }

public:
    vector() {
        store = new int[capacity];
    }
    
    ~vector() {
        delete[]store;
    }
    
    void push_back(int o) {
        store[tail++] = o;
        if (tail == capacity)double_space();
    }
    
    int size() const {
        return tail;
    }
    
    int &operator[](int index) {
        return store[index];
    }
    
    const int &operator[](int index) const {
        return store[index];
    }
};

vector graph[maxn];
bool is_root[maxn];
int wait_list[maxn];
int input_wait_list[maxn];
bool temp_save[maxn] = {false};
int n, u, v, root = 1, head = 0, tail = 0, temp_head;

bool judge() {
    int now_node = root, input_now_node;
    wait_list[tail] = root;
    cin >> input_now_node;
    input_wait_list[tail++] = input_now_node;
    if (input_now_node != now_node)return false;
    while (head < tail) {
        now_node = wait_list[head];
        temp_head = tail;
        for (int i = 0; i < graph[now_node].size(); i++) {
            cin >> input_now_node;
            input_wait_list[tail] = input_now_node;
            wait_list[tail++] = graph[now_node][i];
        }
        //check [temp_head, tail) is same
        for (int i = temp_head; i < tail; i++)temp_save[wait_list[i]] = true;
        for (int i = temp_head; i < tail; i++)
            if (!temp_save[input_wait_list[i]])return false;
        for (int i = temp_head; i < tail; i++)temp_save[wait_list[i]] = false;
        for (int i = temp_head; i < tail; i++)wait_list[i] = input_wait_list[i];
        head++;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        graph[u].push_back(v);
    }
    if (judge())cout << "No" << endl;
    else cout << "Yes" << endl;
    return 0;
}