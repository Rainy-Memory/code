//
// Created by Rainy Memory on 2020/11/30.
//

#include <iostream>
using namespace std;
const int maxn=55;
int m,n;
int value[maxn][maxn]={0};
int p[maxn][maxn][maxn+maxn]={0};

int main(){
    //p[x1][x2][k]=max(p[x1-1][x2][k-1],p[x1][x2-1][k-1]);
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin>>value[i][j];
        }
    }
    for(int k=2;k<=m+n;k++){
        //x1 = i, x2 = j;
        //    i =   1,   2, ..., k-1;
        //k - i = k-1, k-2, ...,   1;
        for(int i=1;i<=m;i++){
            for(int j=i;j<=n;j++){
            
            }
        }
    }
    cout<<p[m][n]<<endl;
    
    
    return 0;
}