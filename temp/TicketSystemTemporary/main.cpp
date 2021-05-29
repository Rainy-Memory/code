//
// Created by Rainy Memory on 2021/5/25.
//

#include "HashMap.h"
#include "AlternativeMultiBPlusTree.h"
#include <iostream>
#include "BPlusTree.h"

using namespace std;

class classa {
public:
    int a;
    int b;
    int c;
    
    classa(int aa, int bb, int cc) : a(aa), b(bb), c(cc) {}
    
    friend ostream &operator<<(ostream &os, const classa &o) {
        os << o.a << " " << o.b << " " << o.c;
        return os;
    }
};

int main() {
    RainyMemory::BPlusTree<int, int> bptr("abc.txt");
    classa a[2] {{1, 2, 3},
                 {4, 5, 6}};
    cout << a[0] << endl;
    int b = 17120;
    memcpy(&a[0], &b, sizeof(int));
    cout << a[0] << endl;
    return 0;
}