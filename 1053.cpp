//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>
using namespace std;
int n;
const int maxn=1e5+1e2;
vector<int> adjacent[maxn];
vector<int> son_node[maxn];
int father_node[maxn]={0};
bool chosen[maxn]={false};
double result=0;

void initialize_tree(int father){
    for(auto i:adjacent[father]){
        if(!chosen[i]){
            son_node[father].push_back(i);
            father_node[i]=father;
            chosen[i]=true;
            initialize_tree(i);
        }
    }
}

struct bfs{
    int point=1;
    int length=0;
    double possibility=1;
};

queue<bfs> q;

int main(){
    //input
    cin>>n;
    for(int i=1;i<n;i++){
        int n1,n2;
        cin>>n1>>n2;
        adjacent[n1].push_back(n2);
        adjacent[n2].push_back(n1);
    }
    
    //initialize a tree    set root 1
    chosen[1]=true;
    father_node[1]=-1;
    initialize_tree(1);
    
    bfs start;
    q.push(start);
    while(!q.empty()){
        int l=q.front().length,poi=q.front().point;
        double pos=q.front().possibility;
        q.pop();
        int sonpoint=son_node[poi].size();
        if(sonpoint==0){
            result+=(pos*l);
        }
        else {
            l++;
            pos/=sonpoint;
            for(auto i:son_node[poi]){
                bfs temp;
                temp.point=i;
                temp.possibility=pos;
                temp.length=l;
                q.push(temp);
            }
        }
    }
    cout<<setiosflags(ios::fixed)<<setprecision(2);
    cout<<result<<endl;
    return 0;
}