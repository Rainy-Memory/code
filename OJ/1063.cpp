//
// Created by Rainy Memory on 2020/11/29.
//

#include <iostream>

using namespace std;
int t, m;
int f[105][1005]={0};
int v[105]={0},p[105]={0};

int max_num(int a, int b) {
    return (a > b ? a : b);
}

int main() {
    cin >> t >> m;
    for(int i=1;i<=m;i++){
        cin>>p[i]>>v[i];
    }
    //f[i][j]: consider 1-i mushroom, use up to j time
    //f[i][j] = f[i - 1][j] or f[i - 1][j - p[i]] + v[i];
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= t; j++) {
            f[i][j]=(j>=p[i])?max_num(f[i-1][j],f[i-1][j-p[i]]+v[i]):f[i-1][j];
        }
    }
    cout<<f[m][t]<<endl;
    
    return 0;
}