//
// Created by Rainy Memory on 2021/1/9.
//

#include <iostream>
#include <chrono>

using namespace std;

int main() {
    long long timeStamp;
    std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch());
    timeStamp = (long long)(ns.count());
    cout<<timeStamp<<endl;
    return 0;
}