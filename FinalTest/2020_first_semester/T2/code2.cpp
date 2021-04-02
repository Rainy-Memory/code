#include <iostream>
#include"code2.hpp"
using namespace std;
	
int main() {
	int n, m, type;
	cin >> n >> m;
	CircleSet set(n);
	cin >> set; //输入集合中的所有圆
	while (m--) {
		int type, p, q;
		cin >> type;
		if (type == 1) {
			//do nothing 
		} else if (type == 2) {
			for (int i = 0; i < n; ++i) {
				cout << set[i] << ' ';
			}
			cout << endl;
		} else if (type == 3) {
			cin >> p >> q;
			cout << set.checkContaining(p, q) << endl;
		} else if (type == 4) {
			cin >> q;
			cout << set.getCircleContainingQ(q) << endl;
		}
	}
	return 0;
}