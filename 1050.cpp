#include <iostream>
#include <vector>
using namespace std;
int n,k;
const int maxn=1e5+1e2;
vector<int> adjacent[maxn];
vector<int> son_node[maxn];
int father_node[maxn]={0};
int lower_point[maxn]={0};
bool chosen[maxn]={false};

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

int calculate_lower_point(int father){
    int sum=1;
    for(auto i:son_node[father]){
        int low=calculate_lower_point(i);
        sum+=low;
    }
    lower_point[father]=sum;
    return sum;
}

int main() {
    //input
    cin>>n>>k;
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
    calculate_lower_point(1);
    int s=0;
    for(int i=n;i>=1;i--){
        bool judge=true;
        for(auto j:son_node[i]){
            if(lower_point[j]>k)judge=false;
        }
        if((n-lower_point[i])>k)judge=false;
        if(judge){
            s++;
            if(s==1)cout<<i;
            else cout<<" "<<i;
        }
    }


    if(s==0)cout<<"None"<<endl;

    return 0;
}