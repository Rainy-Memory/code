//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
#include <cstring>
#include <utility>
#include <iomanip>
#include <vector>
#include <map>
#include <queue>

using namespace std;

struct son0 {
    vector<long long> sonpoint;
};
struct father0 {
    long long fatherpoint = 0;
    long long distance = 0;
};

map<long long, father0> father;
map<long long, son0> son;
long long root;
long long low_poi[10010] = { 0 };

long long lower_point(long long point) {
    if (low_poi[point] != 0) {
        return low_poi[point];
    }
    else {
        if (son[point].sonpoint.size() == 0) {
            low_poi[point] = 1;
            return 1;
        }
        else {
            long long num = 1;
            for (long long i : son[point].sonpoint) {
                num += lower_point(i);
            }
            low_poi[point] = num;
            return num;
        }
    }
}

int main() {
    int n;
    cin >> n;
    for (long long i = 1; i <= n; i++) {
        long long f, d;
        cin >> f >> d;
        father[i].fatherpoint = f;
        father[i].distance = d;
        son[f].sonpoint.push_back(i);
    }
    root = son[0].sonpoint[0];
    //cout << root << endl;
    double sum = 0;
    for (long long i = 1; i <= n; i++) {
        if (i != root) {
            long long num = lower_point(i);
            //cout << i << " " << lower_point(i) << endl;
            sum += father[i].distance * num * (n - num);
        }
    }
    long long cn2 = n * (n - 1) / 2;
    sum /= cn2;
    cout << setiosflags(ios::fixed) << setprecision(2);
    cout << sum << endl;
    return 0;
}