//
// Created by Rainy Memory on 2021/3/29.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

class Tree {
private:
    class Node {
    public:
        Node *parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
        int value = -1;
        bool buildLeft = true;
        
        Node(Node *p, int v) : parent(p), value(v) {}
    };
    
    Node *root = nullptr;
    
    inline bool read(int &o) {
        char c = getchar();
        while (c < '0' || c > '9') {
            if (c == '.')return false;
            c = getchar();
        }
        o = 0;
        while (c >= '0' && c <= '9')o = (o << 3) + (o << 1) + c - '0', c = getchar();
        return true;
    }
    
    void recursionDestruct(Node *now) {
        if (now == nullptr)return;
        recursionDestruct(now->left);
        recursionDestruct(now->right);
        delete now;
    }
    
    void recursionInOrder(Node *now) {
        if (now == nullptr)return;
        recursionInOrder(now->left);
        printf("%d ", now->value);
        recursionInOrder(now->right);
    }
    
    void recursionPostOrder(Node *now) {
        if (now == nullptr)return;
        recursionPostOrder(now->left);
        recursionPostOrder(now->right);
        printf("%d ", now->value);
    }

public:
    void build() {
        int v;
        Node *pa = nullptr;
        while (true) {
            if (read(v)) {
                if (pa == nullptr) {
                    root = new Node(nullptr, v);
                    pa = root;
                }
                else {
                    if (pa->buildLeft) {
                        pa->left = new Node(pa, v);
                        pa = pa->left;
                    }
                    else {
                        pa->right = new Node(pa, v);
                        pa = pa->right;
                    }
                }
            }
            else {
                if (pa->buildLeft) {
                    pa->left = nullptr;
                    pa->buildLeft = false;
                }
                else {
                    pa->right = nullptr;
                    while (pa != nullptr && !pa->buildLeft) {
                        pa = pa->parent;
                    }
                    if (pa == nullptr)break;
                    pa->buildLeft = false;
                }
            }
        }
    }
    
    void inOrderTraversal() {
        recursionInOrder(root);
        puts("");
    }
    
    void postOrderTraversal() {
        recursionPostOrder(root);
        puts("");
    }
    
    ~Tree() {
        recursionDestruct(root);
    }
};

int main() {
    Tree tree;
    tree.build();
    tree.inOrderTraversal();
    tree.postOrderTraversal();
    return 0;
}