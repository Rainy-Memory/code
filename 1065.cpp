//
// Created by Rainy Memory on 2020/11/30.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int n = 0;
int a[10005] = {0};
string str[1005];

//sort
template <class T>
void sort(T *array, int start, int end, bool (*compare)(T,T)){
    for(int i=start;i<=end;i++){
        for(int j=start;j<end-i;j++){
            if(!compare(array[j],array[j+1])){
                T temp=array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
            }
        }
    }
}

bool IncreaseInt(int x,int y) { return x < y; }
bool DecreaseInt(int x,int y) { return y < x; }
bool IncreaseString(string x, string y) { return x < y; }
bool DecreaseString(string x, string y) { return y < x; }

int main()
{
    //主程序中仅此处允许添加必要的代码。其余部分不可修改。
    int op;
    char chh[100];
    scanf("%d",&op);
    switch (op)
    {
        case 0:
            scanf("%d",&n);
            for (int i=0;i<n;++i) scanf("%d",&a[i]);
            sort(a,0,n-1,IncreaseInt);
            for (int i=0;i<n;++i) printf("%d ",a[i]);
            break;
        case 1:
            scanf("%d",&n);
            for (int i=0;i<n;++i) scanf("%d",&a[i]);
            sort(a,0,n-1,DecreaseInt);
            for (int i=0;i<n;++i) printf("%d ",a[i]);
            break;
        case 2:
            scanf("%d",&n); cin.getline(chh,90);
            for (int i=0;i<n;++i) cin >> str[i];
            sort(str,0,n-1,IncreaseString);
            for (int i=0;i<n;++i) cout << str[i] << " ";
            break;
        case 3:
            scanf("%d",&n); cin.getline(chh,90);
            for (int i=0;i<n;++i) cin >> str[i];
            sort(str,0,n-1,DecreaseString);
            for (int i=0;i<n;++i) cout << str[i] << " ";
            break;
    }
    return 0;
}