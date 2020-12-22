#include <iostream>
#include <cstdio>

using namespace std;

namespace LIST {
    
    struct NODE {
        // TODO finish
        int value=0;
        NODE *next = nullptr;
    };
    
    NODE *head = nullptr;
    int len = 0;
    
    void init() {
        // TODO finish
    }
    
    NODE *move(int i) {
        // TODO finish
        NODE *move_ptr = head;
        for (int j = 0; j < i; j++) {
            move_ptr = move_ptr->next;
        }
        return move_ptr;
    }
    
    void insert(int i, int x) {
        // TODO finish
        if (i > len)return;
        if (len == 0) {
            head = nullptr;
            head = new NODE;
            head->value = x;
            head->next = head;
        }
        else {
            if (i == 0) {
                NODE *pre_head = head;
                NODE *pre_tail = move(len - 1);
                head = new NODE;
                head->value = x;
                head->next = pre_head;
                pre_tail->next = head;
            }
            else {
                //before_add->position i - 1;
                //after_add->position i;
                NODE *before_add = move(i - 1);
                NODE *after_add = before_add->next;
                NODE *temp = new NODE;
                before_add->next = temp;
                temp->value = x;
                temp->next = after_add;
            }
        }
        len++;
    }
    
    void remove(int i) {
        // TODO finish
        if (i > len - 1)return;
        if (i == 0) {
            NODE *tail = move(len - 1);
            NODE *temp = head;
            head = head->next;
            delete temp;
            if(len!=1)tail->next = head;
        }
        else {
            NODE *before_remove = move(i - 1);
            NODE *remove_ptr = before_remove->next;
            NODE *after_remove = remove_ptr->next;
            delete remove_ptr;
            before_remove->next = after_remove;
        }
        len--;
        if (len == 0)head = nullptr;
        else if (len == 1)head->next = head;
    }
    
    void remove_insert(int i) {
        //TODO finish
        if (i > len - 1)return;
        if (i == 0) {
            head = head->next;
        }
        else {
            NODE *tail = move(len - 1);
            NODE *before_remove = move(i - 1);
            NODE *remove_ptr = before_remove->next;
            NODE *after_remove = remove_ptr->next;
            if(tail==remove_ptr){
                //do nothing
            }
            else {
                int store_delete = remove_ptr->value;
                delete remove_ptr;
                before_remove->next = after_remove;
                tail->next = new NODE;
                tail->next->next = head;
                tail->next->value = store_delete;
            }
        }
    }
    
    void get_length() {
        // TODO finish
        cout << len << endl;
    }
    
    void query(int i) {
        // TODO finish
        if (i >= len) {
            cout << -1 << endl;
            return;
        }
        NODE *query_ptr = move(i);
        int query_value = query_ptr->value;
        cout << query_value << endl;
    }
    
    void get_max() {
        // TODO finish
        NODE *temp = head;
        int max = -1;
        for (int i = 0; i < len; i++) {
            if (max < temp->value)max = temp->value;
            temp = temp->next;
        }
        cout << max << endl;
    }
    
    void clear() {
        // TODO finish
        NODE *temp = head;
        for (int i = 0; i < len; i++) {
            head = head->next;
            delete temp;
            temp = head;
        }
        len = 0;
    }
}
int n;

int main() {
    cin >> n;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_) {
        cin >> op;
        switch (op) {
            case 0:
                LIST::get_length();
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p, x);
                break;
            case 2:
                cin >> p;
                LIST::query(p);
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                cin >> p;
                LIST::remove_insert(p);
                break;
            case 5:
                LIST::get_max();
                break;
        }
    }
    LIST::clear();
    return 0;
}