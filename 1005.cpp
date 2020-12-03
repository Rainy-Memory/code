//
// Created by Rainy Memory on 2020/12/3.
//

# include <iostream>
# include <stdio.h>

using namespace std;

struct LinkList {
    // TODO: Define some variables of struct LinkList here.
    //1-based!!!!!!!!!!!
    struct LinkListElement {
        int value = 0;
        LinkListElement *next = nullptr;
    };
    int len = 0;
    LinkListElement *head = nullptr;
    
    LinkListElement *i_th_element(int i) {
        LinkListElement *temp = head;
        for (int j = 1; j < i; j++) {
            temp = temp->next;
        }
        return temp;
    }
    
    void Initialize(int *a, int n) {
        // TODO: use a[0 ... n-1] to initialize the link list.
        if (n == 1) {
            head = new LinkListElement;
            head->value = a[0];
            head->next = nullptr;
        }
        else {
            head = new LinkListElement;
            LinkListElement *temp = head;
            for (int i = 0; i < n - 1; i++) {
                temp->value = a[i];
                temp->next = new LinkListElement;
                temp = temp->next;
            }
            temp->value = a[n - 1];
            temp->next = nullptr;
        }
        len = n;
    }
    
    void Insert(int i, int x) {
        // TODO: insert element x after i-th element.
        LinkListElement *temp = new LinkListElement;
        if (i == 0) {
            temp->value = x;
            temp->next = head;
            head = temp;
        }
        else if (i > 0 && i < len) {
            LinkListElement *i_th = i_th_element(i);
            temp->value = x;
            temp->next = i_th->next;
            i_th->next = temp;
        }
        else if (i == len) {
            LinkListElement *tail = i_th_element(len);
            temp->value = x;
            temp->next = nullptr;
            tail->next = temp;
        }
        len++;
    }
    
    void Delete(int i) {
        // TODO: delete element i
        
    }
    
    void EvenOddSwap() {
        // TODO: Swap the even-indexed element with the corresponding odd-indexed element.
    }
    
    void Query(int i) {
        // TODO: Print the value of the i-th element on the screen.
    }
    
    void QueryAll() {
        // TODO: Print the link list on the screen.
    }
    
    void ClearMemory() {
        // TODO: Clear the memory.
    }
};

LinkList L;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n, *a;
    cin >> n;
    a = new int[n];
    for (int i = 0; i < n; ++i) cin >> a[i];
    L.Initialize(a, n);
    delete[] a;
    
    int m, op, i, x;
    cin >> m;
    while (m--) {
        cin >> op;
        switch (op) {
            case 1:
                cin >> i >> x;
                L.Insert(i, x);
                break;
            case 2:
                cin >> i;
                L.Delete(i);
                break;
            case 3:
                L.EvenOddSwap();
                break;
            case 4:
                cin >> i;
                L.Query(i);
                break;
            case 5:
                L.QueryAll();
                break;
        }
    }
    
    L.ClearMemory();
    return 0;
}