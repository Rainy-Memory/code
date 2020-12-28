#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
//#define test_terminal
#define basic_test
//#define test
//#define test_rational
//#define test_matrix
using namespace std;

#ifdef test_terminal
int main(int argc,char* argv[]){

}
#endif

#ifdef basic_test

int main() {
    //cout<<(int)"👀"<<endl;
    fstream fs;
    fs.open("testbi.in", fstream::out | fstream::binary);
    int write_num[10]={123,8739,2789,546,56,63,35,234,324,324},ptr;
    for (int i = 0; i < 10; i++) {
        ptr=write_num[i];
        fs.write(reinterpret_cast<char *>(&ptr), sizeof(int));
    }
    fs.close();
    fs.open("testbi.in", fstream::in | fstream::binary);
    int j;
    fs.read(reinterpret_cast<char *>(&j), sizeof(int));
    while (!fs.eof()) {
        cout << j << " ";
        fs.read(reinterpret_cast<char *>(&j), sizeof(int));
    }
    fs.close();
}

#endif

#ifdef test
class tc{
    //test class
private:
    int value=0;
public:
    void execute();
};

void tc::execute() {
    cout<<"hello world"<<endl;
}

template<class T>
void reverse(T *a, int n) {
    if (n == 1 || n == 0)return;
    T tmp = a[0];
    a[0] = a[n - 1];
    a[n - 1] = tmp;
    reverse(a + 1, n - 2);
}

int main() {
    char* a="abc";
    char b[4];
    strcpy(b,a);
    if(b[3]=='\0')cout<<"yes";
    return 0;
}
#endif

#ifdef test_rational
#include "Rational.h"

int main(){
    Rational a(1,1);
    ++a++;
    
    return 0;
}
#endif

#ifdef test_matrix
#include "matrix.hpp"
int main() {
    sjtu::Matrix<int> a;
    cin>>a;
    sjtu::Matrix<int> b(a);
    for(int i=0;i<a.columnLength();i++){
        cout<<a<<endl;
        a=a*b;
    }
    return 0;
}
#endif
