//
// Created by Rainy Memory on 2021/4/12.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

namespace sjtu {
    class exception : public std::exception {
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
                h1->swap();
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

using namespace std;

struct cmp {
    bool operator()(int o1, int o2) {
        return o1 > o2;
    }
};

#define maxn 300007

int n, m, charm, op, a, b;
sjtu::priority_queue<int, cmp> q[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> charm;
        q[i].push(charm);
    }
    while (m--) {
        cin >> op;
        switch (op) {
            case 0:
                cin >> a >> b;
                q[a].merge(q[b]);
                break;
            case 1:
                cin >> a;
                if (q[a].empty()) {
                    cout << "-1" << endl;
                }
                else {
                    charm = q[a].top();
                    q[a].pop();
                    cout << charm << endl;
                }
                break;
            default:
                cin >> a >> b;
                q[a].push(b);
                break;
        }
    }
    return 0;
}