//
// Created by Rainy Memory on 2020/12/29.
//

#include <iostream>

using namespace std;

int main() {
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    int time1=a*60+b,time2=c*60+d;
    int dt=time2-time1;
    int hour=dt/60,minute=dt%60;
    cout<<hour<<" "<<minute<<endl;
    return 0;
}