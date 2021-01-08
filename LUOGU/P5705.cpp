//
// Created by Rainy Memory on 2020/12/29.
//

#include <iostream>
using namespace std;
int main(){
    int a1,a2;
    char point;
    cin>>a1>>point>>a2;
    int b=0;
    b+=a1%10;
    a1/=10;
    b*=10;
    b+=a1%10;
    a1/=10;
    b*=10;
    b+=a1;
    cout<<a2<<"."<<b<<endl;
    return 0;
}