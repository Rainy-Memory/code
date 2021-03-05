//
// Created by Rainy Memory on 2021/2/26.
//

#include <iostream>

using namespace std;

//int arr[1000007] = {0};
//int len = 0;
//
//void insert(int index, int value) {
//    for (int i = len + 1; i > index; i--)arr[i + 1] = arr[i];
//    arr[index + 1] = value;
//    len++;
//}
//
//void erase(int index) {
//    for (int i = index; i < len; i++)arr[i] = arr[i + 1];
//    len--;
//}
//
//void print() {
//    for (int i = 1; i <= len; i++)cout << arr[i] << " ";
//    cout << endl;
//}
//
//int main() {
//    int n, m;
//    cin >> n >> m;
//    for (int i = 1; i <= n; i++)cin >> arr[i];
//    len = n;
//    for (int i = 0; i < m; i++) {
//        int op;
//        cin >> op;
//        if (op == 1) {
//            int index, value;
//            cin >> index >> value;
//            insert(index, value);
//        }
//        else {
//            int index;
//            cin >> index;
//            erase(index);
//        }
//    }
//    print();
//    return 0;
//}
template<class T>
class LinkedList {
private:
    class Node {
    public:
        T value = 0;
        Node *next = nullptr;
        Node *pre = nullptr;
        
        Node() = default;
        
        explicit Node(const T &o) : value(o) {}
        
        ~Node() = default;
    };
    
    Node *head = nullptr;
    Node *tail = nullptr;
    int len = 0;

public:
    LinkedList() {
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->pre = head;
    }
    
    ~LinkedList() {
        Node *temp = head;
        while (head != nullptr) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }
    
    void push_back(const T &o) {
        Node *temp = new Node(o);
        temp->next = tail;
        temp->pre = tail->pre;
        tail->pre->next = temp;
        tail->pre = temp;
        len++;
    }
    
    void initialize(int n) {
        for (int i = 0; i < n; i++) {
            T val;
            cin >> val;
            push_back(val);
        }
    }
    
    Node *findNode(int index) {
        if (index < len / 2) {
            Node *temp = head;
            for (int i = 0; i < index; i++)temp = temp->next;
            return temp;
        }
        else {
            Node *temp = tail;
            for (int i = 0; i < (len + 1 - index); i++)temp = temp->pre;
            return temp;
        }
    }
    
    void insert(int index, const T &o) {
        //insert after index
        Node *temp = findNode(index);
        Node *newNode = new Node(o);
        newNode->next = temp->next;
        newNode->pre = temp;
        temp->next->pre = newNode;
        temp->next = newNode;
        len++;
    }
    
    void erase(int index) {
        Node *eraseNode = findNode(index);
        eraseNode->next->pre = eraseNode->pre;
        eraseNode->pre->next = eraseNode->next;
        delete eraseNode;
        len--;
    }
    
    void print() const {
        Node *temp = head->next;
        while (temp != tail) {
            cout << temp->value << " ";
            temp = temp->next;
        }
    }
};

int main() {
    LinkedList<int> list;
    int n, m;
    cin >> n >> m;
    list.initialize(n);
    for (int i = 0; i < m; i++) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int index, value;
            cin >> index >> value;
            list.insert(index, value);
        }
        else {
            int index;
            cin >> index;
            list.erase(index);
        }
    }
    list.print();
    return 0;
}