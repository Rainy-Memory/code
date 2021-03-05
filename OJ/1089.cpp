//
// Created by Rainy Memory on 2021/2/26.
//

#include <iostream>
#include <cstring>

using namespace std;

int t, n, m;
unsigned int like[65], dislike[65];
const unsigned int unit = 1;

inline void readline() {
    int num;
    for (int i = 0; i < m; i++) {
        do {
            cin >> num;
            if (num > 0)like[i] |= unit << ((unsigned int) (num - 1));
            else dislike[i] |= unit << ((unsigned int) (-num - 1));
        } while (getchar() != '\r');
        getchar();
    }
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> m;
        memset(like, 0, sizeof(like));
        memset(dislike, 0, sizeof(dislike));
        readline();
        bool flag = false;
        for (unsigned int i = 0; i < (unit << n); i++) {
            int cnt = 0;
            for (int j = 0; j < m; j++) {
                if (((like[j] & i) != 0) || ((dislike[j] & (~i)) != 0))cnt++;
            }
            if (cnt == m) {
                flag = true;
                break;
            }
        }
        if (flag)cout << "Bingo!" << endl;
        else cout << "Sigh..." << endl;
    }
    return 0;
}