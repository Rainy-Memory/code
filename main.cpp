#include <iostream>
#include <cstring>

using namespace std;

int main() {
    int a[10];
    memset(a, -1, sizeof(a));
    for (auto i:a)cout << i << endl;
    return 0;
}