#include "code1.hpp"

using namespace std;

int main() {
    int len, m;
    scanf("%d%d", &len, &m);
    LinkListArray a = LinkListArray(len);
    for (int i = 0, op, s1, s2; i < m; ++i) {
        scanf("%d%d%d", &op, &s1, &s2);
        if (op == 0) {
            a.insertNumber(s1, s2);
        }
        if (op == 1) {
            //printf("%d\n", a.queryNumber(s1, s2));
            std::cout << a.queryNumber(s1, s2) << std::endl;
        }
        if (op == 2) {
            a.mergeLists(s1, s2);
        }
    }
    return 0;
}
