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

#include "ArbitraryPrecisionInt.h"

int main() {
    ArbitraryPrecisionInt a, b;
    while (cin >> a >> b) {
        cout << a + b << endl;
        cout << a - b << endl;
        cout << a * b << endl;
        cout << a / b << endl;
        cout << a % b << endl;
    }
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
