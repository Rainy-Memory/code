//
// Created by Rainy Memory on 2021/2/26.
//

#include <iostream>
#include <cstddef>
#include <functional>
#include <cstring>
#include <string>

using namespace std;

#define MAXN 6000007

int w[MAXN] = {0};
int pre[MAXN] = {0};
int nxt[MAXN] = {0};
bool deleted[MAXN] = {false};
int ans[MAXN] = {0};//if(erase[i]) { ans[i] == erased element's weight }, -1 represent query max weight, others is ans.
bool invalid[MAXN] = {false};
bool erase[MAXN] = {false};//No.i operation is erase a number.

namespace sjtu {
    class exception {
    protected:
        const std::string variant = "";
        std::string detail = "";
    public:
        exception() {}
        
        exception(const exception &ec) : variant(ec.variant), detail(ec.detail) {}
        
        virtual std::string what() {
            return variant + " " + detail;
        }
    };
    
    class index_out_of_bound : public exception {
        /* __________________________ */
    };
    
    class runtime_error : public exception {
        /* __________________________ */
    };
    
    class invalid_iterator : public exception {
        /* __________________________ */
    };
    
    class container_is_empty : public exception {
        /* __________________________ */
    };

/**
 * a container like std::priority_queue which is a heap internal.
 */
    template<typename T, class Compare = std::less<T>>
    class priority_queue {
    private:
        class skewHeap {
        private:
            class Node {
            public:
                T *value = nullptr;
                Node *leftChild = nullptr;
                Node *rightChild = nullptr;
                
                Node() = default;
                
                Node(const Node &o) {
                    value = new T(*(o.value));
                }
                
                explicit Node(const T &o) {
                    value = new T(o);
                }
                
                ~Node() {
                    delete value;
                }
                
                void swap() {
                    Node *temp = leftChild;
                    leftChild = rightChild;
                    rightChild = temp;
                }
            };
            
            Node *root = nullptr;
            size_t nodeNum = 0;
            
            void constructHeap(Node *src, Node *&target) {
                if (src == nullptr)return;
                target = new Node(*(src->value));
                constructHeap(src->leftChild, target->leftChild);
                constructHeap(src->rightChild, target->rightChild);
            }
            
            void destructHeap(Node *now) {
                if (now == nullptr)return;
                destructHeap(now->leftChild);
                destructHeap(now->rightChild);
                delete now;
            }
            
            Node *mergeHeap(Node *h1, Node *h2) {
                if (h1 == nullptr)return h2;
                if (h2 == nullptr)return h1;
                Compare cmp;
                if (cmp(*h1->value, *h2->value)) {
                    Node *temp = h1;
                    h1 = h2;
                    h2 = temp;
                }
                h1->rightChild = mergeHeap(h1->rightChild, h2);
                int judge = rand() % 2;
                if (judge)h1->swap();
                return h1;
            }
        
        public:
            
            skewHeap() = default;
            
            skewHeap(const skewHeap &o) : nodeNum(o.nodeNum) {
                constructHeap(o.root, root);
            }
            
            skewHeap &operator=(const skewHeap &o) {
                if (this == &o)return *this;
                clear();
                root = nullptr;
                nodeNum = o.nodeNum;
                constructHeap(o.root, root);
                return *this;
            }
            
            ~skewHeap() {
                destructHeap(root);
            }
            
            void clear() {
                destructHeap(root);
                nodeNum = 0;
            }
            
            void push(const T &o) {
                Node *h = new Node(o);
                root = mergeHeap(root, h);
                nodeNum++;
            }
            
            void pop() {
                Node *temp = root;
                root = mergeHeap(root->leftChild, root->rightChild);
                delete temp;
                nodeNum--;
            }
            
            void merge(skewHeap &o) {
                nodeNum += o.nodeNum;
                root = mergeHeap(root, o.root);
                o.root = nullptr;
                o.nodeNum = 0;
            }
            
            const T &top() const {
                return *(root->value);
            }
            
            size_t size() const {
                return nodeNum;
            }
        };
        
        skewHeap heap;
    
    public:
        priority_queue() {}
        
        priority_queue(const priority_queue &other) : heap(other.heap) {}
        
        ~priority_queue() {}
        
        priority_queue &operator=(const priority_queue &other) {
            if (this == &other)return *this;
            heap = other.heap;
            return *this;
        }
        
        const T &top() const {
            if (empty())throw container_is_empty();
            return heap.top();
        }
        
        void push(const T &e) {
            heap.push(e);
        }
        
        void pop() {
            if (empty())throw container_is_empty();
            heap.pop();
        }
        
        size_t size() const {
            return heap.size();
        }
        
        bool empty() const {
            return heap.size() == 0;
        }
        
        void merge(priority_queue &other) {
            heap.merge(other.heap);
        }
    };
    
}

class Weight {
public:
    int weight;
    int index;
    
    Weight(int _w, int _i) : weight(_w), index(_i) {}
    
    bool operator<(const Weight &o) const {
        return weight < o.weight;
    }
};

inline void read(int &o) {
    char c = getchar();
    bool negative = false;
    while (c > '9' || c < '0') {
        if (c == '-')negative = true;
        c = getchar();
    }
    o = 0;
    while (c <= '9' && c >= '0') {
        o = o * 10 + c - '0';
        c = getchar();
    }
    if (negative)o *= -1;
}

void solveSmall(int n) {
    int q;
    sjtu::priority_queue<Weight> pq;
    for (int i = 1; i <= n; i++) {
        read(w[i]);
        Weight temp(w[i], i);
        pq.push(temp);
        pre[i] = i == 1 ? n : i - 1;
        nxt[i] = i == n ? 1 : i + 1;
    }
    read(q);
    int op, x;
    for (int i = 0; i < q; i++) {
        read(op);
        if (op == 0) {
            read(x);
            if (!deleted[x]) {
                deleted[x] = true;
                nxt[pre[x]] = nxt[x];
                pre[nxt[x]] = pre[x];
            }
        }
        else if (op == 1) {
            char opt = getchar();
            while (true) {
                if (opt == 'P' || opt == 'N')break;
                opt = getchar();
            }
            read(x);
            if (opt == 'P') {
                if (deleted[x])puts("Invalid.");
                else printf("%d\n", pre[x]);
            }
            else {
                if (deleted[x])puts("Invalid.");
                else printf("%d\n", nxt[x]);
            }
        }
        else {
            while (!pq.empty() && deleted[pq.top().index]) {
                pq.pop();
            }
            if (pq.empty())puts("Invalid.");
            else printf("%d\n", pq.top().weight);
        }
    }
}

void solveBig(int n) {
    //todo debug... still WA, can only handle huge data
    int q;
    for (int i = 1; i <= n; i++) {
        read(w[i]);
        pre[i] = i == 1 ? n : i - 1;
        nxt[i] = i == n ? 1 : i + 1;
    }
    read(q);
    int op, x;
    for (int i = 1; i <= q; i++) {
        read(op);
        if (op == 0) {
            read(x);
            if (!deleted[x]) {
                deleted[x] = true;
                nxt[pre[x]] = nxt[x];
                pre[nxt[x]] = pre[x];
                nxt[x] = -1;
                pre[x] = -1;
                ans[i] = w[x];
                erase[i] = true;
            }
            else invalid[i] = true;
        }
        else if (op == 1) {
            char opt = getchar();
            while (true) {
                if (opt == 'P' || opt == 'N')break;
                opt = getchar();
            }
            read(x);
            if (opt == 'P') {
                if (deleted[x])invalid[i] = true;
                else ans[i] = pre[x];
            }
            else {
                if (deleted[x])invalid[i] = true;
                else ans[i] = nxt[x];
            }
        }
        else ans[i] = -1;
    }
    int maxNum = -1;
    for (int i = 1; i <= n; i++) {
        if (!deleted[i] && maxNum < w[i])maxNum = w[i];
    }
    for (int i = q; i > 0; i--) {
        if (!invalid[i]) {
            if (ans[i] == -1) {
                if (maxNum != -1)ans[i] = maxNum;
                else invalid[i] = true;
            }
            else if (erase[i]) {
                if (maxNum < ans[i])maxNum = ans[i];
            }
        }
    }
    for (int i = 1; i <= q; i++) {
        if (invalid[i] && !erase[i])puts("Invalid.");
        else if (!erase[i])printf("%d\n", ans[i]);
    }
}

int main() {
    int n;
    read(n);
    if (n <= 1000000)solveSmall(n);
    else solveBig(n);
    return 0;
}