#include <iostream>
#include <iomanip>
//#define test_matrix
#define test

using namespace std;


#ifdef test

class devidebyzero {
};

class error2 {
};

void f(int a) {
    if (a == 0)throw devidebyzero();
    else throw error2();
}

int main() {
    for (int i = 0; i < 2; i++) {
        try {
            f(i);
        } catch (error2) {
            cout << "error2" << endl;
        } catch (devidebyzero) {
            cout << "devidebyzero" << endl;
        }
    }
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
