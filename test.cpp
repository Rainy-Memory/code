#include <iostream>
#include <cstring>
#include <cstdio>
#define maxn 55
using namespace std;
int f[2 * maxn][maxn][maxn];
int a[maxn][maxn];
int n,m;

int max_ele(int a,int b,int c,int d){
    if (b>a)
        a = b;
    if (c>a)
        a = c;
    if (d>a)
        a = d;
    return a;
}

int main(){
    cin >> n >> m;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            cin >> a[i][j];
    for (int k=1;k<=n+m-1;k++)
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++){
                if (k-i+1<1 || k-j+1<1) //这里是判断纵坐标的合法性，如果纵坐标不合法那就跳过去
                    continue;
                f[k][i][j] = max_ele(f[k-1][i][j],f[k-1][i-1][j-1],f[k-1][i][j-1],f[k-1][i-1][j]) + a[i][k-i+1] + a[j][k-j+1];
                if (i==j) //判断重合路径
                    f[k][i][j]-=a[i][k-i+1];
            }
    
    
    cout << f[n+m-1][n][n] << endl;
    return 0;
}