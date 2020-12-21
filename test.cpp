#include <iostream>
#include <iomanip>

using namespace std;

class outOfRange {
};

class outOfIndex {
};

class A {
    int data;
public:
    A(int d = 0) { data = d; }
    
    operator char() const {
        if (data < 0 || data > 25) throw outOfRange();
        return data + 'a';
    }
};

template<class T1, class T2, int N>
class Sample {
    T1 data[N];
public:
    Sample(T2 x[]) { for (int i = 0; i < N; ++i) data[i] = x[i]; }
    
    Sample &operator++() {
        for (int i = 0; i < N; ++i) ++data[i];
        return *this;
    }
    
    T1 &operator[](int n) {
        if (n < 0 || n >= N) throw outOfIndex(); else return data[n];
    }
    
    void disp() const {
        for (int i = 0; i < N; ++i)
            cout << setfill('#') << setw(4) << data[i];
        cout << endl;
    }
};

int main() {
    A a[5];
    
    for (int flag = -1; flag < 1; ++flag) {
        for (int k = 0; k < 5; ++k) a[k] = k + flag;
        try {
            Sample<char, A, 5> ss(a);
            ss.disp();
            ++ss;
            ss.disp();
            ss[5] = 8.9;
            ss.disp();
        } catch (outOfIndex) { cout << "out of index" << endl; }
        catch (outOfRange) { cout << "out of range" << endl; }
    }
    
    return 0;
}
