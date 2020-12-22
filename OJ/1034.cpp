//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
#include <cstring>
#include <utility>
#include <iomanip>
#include <queue>
using namespace std;

struct dataT {
    long long day = 0;
    long long remain = 0;
    double possibility = 0;
};



int main() {
    long long n, m, r;
    double result = 0, sum_pos = 0;
    queue<dataT> q;
    cin >> n >> m;
    r = n - m;
    dataT initial;
    initial.day = 0;
    initial.remain = n;
    initial.possibility = 1;
    q.push(initial);
    while (!q.empty()) {
        long long day = q.front().day, remain = q.front().remain;
        double possibility = q.front().possibility;
        if (remain != r) {
            for (long long i = r; i < remain; i++) {
                dataT temp;
                temp.day = day + 1;
                temp.remain = i;
                temp.possibility = possibility / remain;
                q.push(temp);
            }
        }
        else {
            result += day * possibility;
            sum_pos += possibility;
        }
        q.pop();
    }
    result /= sum_pos;
    cout << setiosflags(ios::fixed) << setprecision(2);
    cout << result << endl;
    return 0;
}