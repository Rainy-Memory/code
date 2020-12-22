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
        else len--;
        len++;
    }
    
    void Delete(int i) {
        // TODO: delete element i
        if (i == 1) {
            LinkListElement *i_th = head;
            LinkListElement *i_th_after = i_th->next;
            delete i_th;
            head = i_th_after;
        }
        else if (i > 1 && i < len) {
            LinkListElement *i_th_before = i_th_element(i - 1);
            LinkListElement *i_th = i_th_before->next;
            LinkListElement *i_th_after = i_th->next;
            i_th_before->next = i_th_after;
            delete i_th;
        }
        else if (i == len) {
            LinkListElement *i_th_before = i_th_element(i - 1);
            LinkListElement *i_th = i_th_before->next;
            delete i_th;
            i_th_before->next = nullptr;
        }
        else len++;
        len--;
    }
    
    void EvenOddSwap() {
        // TODO: Swap the even-indexed element with the corresponding odd-indexed element.
        if(len<=1)return;
        int change_time=len/2;
        int temp=0;
        LinkListElement *odd_ptr=head;
        LinkListElement *even_ptr=head->next;
        if (len % 2) {
            //odd
            for(int i=1;i<=change_time;i++){
                temp=odd_ptr->value;
                odd_ptr->value=even_ptr->value;
                even_ptr->value=temp;
                if(i<change_time){
                    odd_ptr=even_ptr->next;
                    even_ptr=odd_ptr->next;
                }
            }
        }
        else {
            //even
            for(int i=1;i<=change_time;i++){
                temp=odd_ptr->value;
                odd_ptr->value=even_ptr->value;
                even_ptr->value=temp;
                if(i<change_time){
                    odd_ptr=even_ptr->next;
                    even_ptr=odd_ptr->next;
                }
            }
        }
    }
    
    void Query(int i) {
        // TODO: Print the value of the i-th element on the screen.
        LinkListElement *i_th = i_th_element(i);
        cout << i_th->value << endl;
    }
    
    void QueryAll() {
        // TODO: Print the link list on the screen.
        LinkListElement *temp = head;
        for (int i = 0; i < len - 1; i++) {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << temp->value << endl;
    }
    
    void ClearMemory() {
        // TODO: Clear the memory.
        LinkListElement *temp = head;
        for (int i = 0; i < len - 1; i++) {
            head = head->next;
            delete temp;
            temp = head;
        }
        delete head;
        head = nullptr;
        len = 0;
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