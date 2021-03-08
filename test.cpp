#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

class test {
public:
    int *a = nullptr;
    test *next = nullptr;
    
    int *&ret() {
        return a;
    }
};

int main() {
    test *a, *b;
    a=new test;
    b=new test;
    a->next=b;
    a->ret()=new int(10);
    cout<<*(a->a)<<endl;
    return 0;
}