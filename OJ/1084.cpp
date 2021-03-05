//
// Created by Rainy Memory on 2021/2/26.
//

#include <iostream>

using namespace std;

template<class T>
class LinkedList {
private:
    class Node {
    public:
        T value = 0;
        Node *next = nullptr;
        
        Node() = default;
        
        explicit Node(const T &o) : value(o) {}
        
        ~Node() = default;
    };
    
    Node *head;

public:
    LinkedList() {
        head = new Node;
    }
    
    ~LinkedList() {
        Node *temp = head;
        while (head != nullptr) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }
    
    void initialize(int n) {
        Node *tail = head;
        for (int i = 0; i < n; i++) {
            T val;
            cin >> val;
            tail->next = new Node(val);
            tail = tail->next;
        }
    }
    
    Node *findNode(int index) {
        Node *temp = head;
        for (int i = 0; i < index; i++)temp = temp->next;
        return temp;
    }
    
    void insert(int index, const T &o) {
        //insert after index
        Node *temp = findNode(index);
        Node *newNode = new Node(o);
        newNode->next = temp->next;
        temp->next = newNode;
    }
    
    void erase(int index) {
        Node *temp = findNode(index - 1);
        Node *eraseNode = temp->next;
        temp->next = eraseNode->next;
        delete eraseNode;
    }
    
    void print() const {
        Node *temp = head->next;
        while (temp != nullptr) {
            cout << temp->value << " ";
            temp = temp->next;
        }
    }
};


int main() {
    string type;
    cin >> type;
    int n, m;
    cin >> n >> m;
    if (type == "int") {
        LinkedList<int> list1, list2;
        list1.initialize(n);
        list2.initialize(m);
        list1.print();
        list2.print();
    }
    else if(type=="double"){
        LinkedList<double> list1, list2;
        list1.initialize(n);
        list2.initialize(m);
        list1.print();
        list2.print();
    }
    else {
        LinkedList<char> list1, list2;
        list1.initialize(n);
        list2.initialize(m);
        list1.print();
        list2.print();
    }
    return 0;
}