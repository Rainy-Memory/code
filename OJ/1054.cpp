//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int maxn=1e5+1e2;
int n,m;
int f[maxn];
bool marked[maxn]={false};
vector<int> son_node[maxn];

int max_unmarked_int(int max){
    for(int i=max;i>=1;i--){
        if(!marked[i])return i;
    }
    return -1;
}

int main(){
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int ui,vi;
        cin>>ui>>vi;
        son_node[vi].push_back(ui);
    }
    int root;
    root=n;
    queue<int> q;
    while(true){
        q.push(root);
        f[root]=root;
        while(!q.empty()){
            int temproot=q.front();
            marked[temproot]=true;
            q.pop();
            for(auto i:son_node[temproot]){
                if(!marked[i]){
                    q.push(i);
                    f[i]=root;
                }
            }
        }
        root=max_unmarked_int(root);
        if(root==-1)break;
    }
    for(int i=1;i<n;i++){
        cout<<f[i]<<" ";
    }
    cout<<f[n]<<endl;
    return 0;
}