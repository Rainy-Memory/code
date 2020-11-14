#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int maxn = 1e5 + 1e2;
int n, m, k, mincost = -1;
int n1[maxn] = {0}, n2[maxn] = {0}, l[maxn] = {0};
bool material[maxn] = {false};

struct ROAD {
    int length;
    bool can_build_backery;
};
vector<ROAD> road[maxn];


int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        cin >> n1[i] >> n2[i] >> l[i];
    }
    for (int i = 0; i < k; i++) {
        int poi;
        cin >> poi;
        material[poi] = true;
    }
    for (int i = 0; i < m; i++) {
        ROAD temp;
        temp.length = l[i];
        temp.can_build_backery = (!material[n1[i]]);
        road[n2[i]].push_back(temp);
        temp.can_build_backery = (!material[n2[i]]);
        road[n1[i]].push_back(temp);
    }
    for(int i=0;i<n;i++){
        if(material[i]){
            for(auto j:road[i]){
                if(j.can_build_backery){
                    if(mincost==-1||mincost>j.length)mincost=j.length;
                }
            }
        }
    }
    cout<<mincost<<endl;
    return 0;
}