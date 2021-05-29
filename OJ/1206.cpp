//
// Created by Rainy Memory on 2021/5/28.
//

#include <iostream>

using namespace std;

#define maxn 200007
typedef long long ll;
ll value[maxn], prefix[maxn];
int stack[maxn], l[maxn], r[maxn];

int main() {
    ios::sync_with_stdio(false);
    int n, top = 0;
    ll ans = 0;
    cin >> n;
    if (n > 120000) {
        prefix[0] = 0;
        for (int i = 1; i <= n; i++)cin >> value[i], prefix[i] = prefix[i - 1] + value[i];
        for (int i = 1; i <= n; i++) {
            while (top > 0 && value[i] <= value[stack[top]])r[stack[top--]] = i - 1;
            stack[++top] = i;
        }
        for (int i = 1; i <= top; i++)r[stack[i]] = n;
        top = 0;
        for (int i = n; i >= 1; i--) {
            while (top > 0 && value[i] <= value[stack[top]])l[stack[top--]] = i;
            stack[++top] = i;
        }
        for (int i = 1; i <= top; i++)l[stack[i]] = 0;
        for (int i = 1; i <= n; i++)ans = max(ans, value[i] * (prefix[r[i]] - prefix[l[i]]));
        cout << ans << endl;
    }
    else {
        for (int i = 0; i < n; i++)cin >> value[i];
        bool same = true;
        for (int i = 1; i < n; i++) {
            if (value[i - 1] != value[i]) {
                same = false;
                break;
            }
        }
        if (same) {
            cout << value[0] * ll(n) << endl;
            return 0;
        }
        for (int i = 0; i < n; i++) {
            ll sum = value[i];
            int ll = i - 1, rr = i + 1;
            while (value[ll] >= value[i] && ll >= 0)sum += value[ll--];
            while (value[rr] >= value[i] && rr < n)sum += value[rr++];
            ans = max(ans, value[i] * sum);
        }
        cout << ans << endl;
    }
    return 0;
}