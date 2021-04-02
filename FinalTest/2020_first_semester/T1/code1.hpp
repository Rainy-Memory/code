#include <cstdio>
#include<cmath>
#include<iostream>
#include<cstring>

class LinkList {
private:
    struct node {
        int value = 0;
        node *next = nullptr;
    };
    node *head = nullptr;
    int length = 0;

private:
    node *move(int i) {
        if (i >= 0 && i < length) {
            node *temp = head;
            for (int j = 0; j < i; j++) {
                temp = temp->next;
            }
            return temp;
        }
        else return nullptr;
    }

public:
    LinkList() {
    
    }
    
    ~LinkList() {
        if (length > 0) {
            node *temp = head;
            for (int i = 1; i < length; i++) {
                head = head->next;
                delete temp;
                temp = head;
            }
            delete head;
        }
        length = 0;
        head = nullptr;
    }
    
    void delete_head() {
        if (length > 1) {
            node *temp = head->next;
            delete head;
            head = temp;
        }
        else {
            delete head;
            head = nullptr;
        }
        length--;
    }
    
    int head_value() {
        return head->value;
    }

public:
    void push(int x) {
        node *new_node = new node;
        new_node->value = x;
        if (length == 0) {
            head = new_node;
        }
        else if (length == 1) {
            if (head->value <= x) {
                head->next = new_node;
            }
            else {
                new_node->next = head;
                head = new_node;
            }
        }
        else {
            node *temp = head;
            node *temp_next_ptr = temp->next;
            int s = 0;
            if (head->value >= x) {
                (new_node->next) = head;
                head = new_node;
                s++;
            }
            if (s == 0) {
                for (int i = 1; i < length - 1; i++) {
                    if ((temp->value) < x && (temp_next_ptr->value) >= x) {
                        //insert after temp;
                        new_node->next = temp_next_ptr;
                        temp->next = new_node;
                        s++;
                    }
                    else {
                        temp = temp_next_ptr;
                        temp_next_ptr = temp_next_ptr->next;
                    }
                }
                if ((temp->value) < x && (temp_next_ptr->value) >= x) {
                    //insert after temp;
                    new_node->next = temp_next_ptr;
                    temp->next = new_node;
                    s++;
                }
            }
            if ((s == 0) && x > (temp_next_ptr->value)) {
                temp_next_ptr->next = new_node;
            }
        }
        length++;
    }
    
    int getKth(int k) {
        if (k > length - 1 || k < 0)return -1;
        node *now = move(k);
        int Kth_value = now->value;
        return Kth_value;
    }
    
    void merge(LinkList *mix) {
        //node *head_mix = mix->head;
        LinkList new_list;
        int new_length = length + mix->length;
        while (length + mix->length > 0) {
            if (length > 0 && mix->length > 0) {
                int now_head = head_value(), mix_head = mix->head_value();
                if (now_head >= mix_head) {
                    new_list.push(now_head);
                    delete_head();
                }
                else {
                    new_list.push(mix_head);
                    mix->delete_head();
                }
            }
            else if (length == 0 && mix->length > 0) {
                int mix_head = mix->head_value();
                new_list.push(mix_head);
                mix->delete_head();
            }
            else if (length > 0 && mix->length == 0) {
                int now_head = head_value();
                new_list.push(now_head);
                delete_head();
            }
        }
        
        head = new_list.head;
        length = new_length;
        new_list.head = nullptr;
        new_list.length = 0;
    }
    
};

class LinkListArray {
private:
    int len;
    LinkList **lists;

public:
    LinkListArray(int n) : len(n) {
        lists = new LinkList *[n];
        for (int i = 0; i < n; ++i) lists[i] = new LinkList;
    }
    
    ~LinkListArray() {
        for (int i = 0; i < len; ++i) {
            delete lists[i];
        }
        delete[]lists;
    }
    
    void insertNumber(int n, int x) {
        lists[n]->push(x);
    }
    
    int queryNumber(int n, int k) {
        return lists[n]->getKth(k);
    }
    
    void mergeLists(int p, int q) {
        lists[p]->merge(lists[q]);
    }
};