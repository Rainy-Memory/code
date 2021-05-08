//
// Created by Rainy Memory on 2021/4/26.
//

#include <iostream>

using namespace std;

template<class T>
class BinarySearchTree {
private:
    class Node {
    public:
        T value;
        Node *left = nullptr;
        Node *right = nullptr;
        
        explicit Node(const T &o) : value(o) {}
        
        Node() = default;
        
        Node *findRightMin() const {
            Node *ret = const_cast<Node *>(right);
            while (ret->left != nullptr)ret = ret->left;
            return ret;
        }
    };
    
    Node *root = nullptr;
    
    void inner_add(const T &o, Node *&now) {
        if (now == nullptr)now = new Node(o);
        else {
            if (o < now->value)inner_add(o, now->left);
            if (o > now->value)inner_add(o, now->right);
            if (o == now->value)return;
        }
    }
    
    void inner_erase(const T &o, Node *p, Node *father) {
        Node *now = p, *fa = father;
        while (now != nullptr && now->value != o) {
            fa = now;
            if (o < now->value)now = now->left;
            else now = now->right;
        }
        if (now == fa->left)fa->left = now->right;
        else fa->right = now->right;
        delete now;
    }

public:
    void add(const T &o) {
        inner_add(o, root);
    }
    
    void erase(const T &o) {
        Node *now = root, *fa = nullptr;
        while (now != nullptr && now->value != o) {
            fa = now;
            if (o < now->value)now = now->left;
            else now = now->right;
        }
        if (now == nullptr)return;
        //now->value == o
        if (fa == nullptr || now == root) {//now == root
            if (now->right == nullptr) {
                root = now->left;
                delete now;
                return;
            }
            Node *temp = now->findRightMin();
            now->value = temp->value;
            inner_erase(now->value, now->right, now);
            return;
        }
        if (now->right == nullptr) {
            if (now == fa->left)fa->left = now->left;
            else fa->right = now->left;
            delete now;
            return;
        }
        Node *temp = now->findRightMin();
        now->value = temp->value;
        inner_erase(now->value, now->right, now);
    }
    
    void find(const T &o) const {
        string s("*");
        Node *now = root;
        while (now != nullptr && now->value != o) {
            if (o < now->value)now = now->left, s += 'l';
            else now = now->right, s += 'r';
        }
        if (now == nullptr)cout << "Nothing." << endl;
        else cout << s << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    int q, x;
    char op;
    BinarySearchTree<int> bst;
    cin >> q;
    while (q--) {
        cin >> op >> x;
        switch (op) {
            case '+':
                bst.add(x);
                break;
            case '-':
                bst.erase(x);
                break;
            case '*':
                bst.find(x);
                break;
            default:
                cout << "error" << endl;
                break;
        }
    }
    return 0;
}