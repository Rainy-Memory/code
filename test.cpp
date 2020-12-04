#include <iostream>

using namespace std;

int &funA(int a,int b){
    return a;
}


int main() {
    char a='0';
    cout<<a<<endl;
    
    return 0;
}