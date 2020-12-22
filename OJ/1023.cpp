//
// Created by Rainy Memory on 2020/12/4.
//

#include <iostream>
using namespace std;
const int maxn = 1e7 + 1e2;
int a[maxn], l[maxn], r[maxn], n, m, q, L;

unsigned int seed;
unsigned int xorshift() {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}
void generator() {
    for (int i = 1; i <= n; ++i)
        a[i] = xorshift() >> 1u;
    for (int i = 1; i <= q; ++i)
        r[i] = (l[i] = xorshift() % (n - L + 1) + 1) + L - 1;
}

long long prefix[maxn] = { 0 }, suffix[maxn] = { 0 };

int main() {
    cin >> n >> m >> q >> L >> seed;
    generator();
    int q0 = n / L;
    for (int i = 1; i <= n; i++) {
        a[i] %= m;
    }
    for (int i = 0; i < q0; i++) {
        long long pf = 1, sf = 1;
        for (int j = i * L + 1; j <= (i + 1) * L; j++) {
            pf *= a[j];
            pf %= m;
            prefix[j] = pf;
        }
        for (int j = (i + 1) * L; j > i * L; j--) {
            sf *= a[j];
            sf %= m;
            suffix[j] = sf;
        }
    }
    long long pf0 = 1;
    for (int i = q0 * L + 1; i <= n; i++) {
        pf0 *= a[i];
        pf0 %= m;
        prefix[i] = pf0;
    }
    for (int i = 1; i <= q; i++) {
        if (l[i] % L != 1) {
            long long result = (suffix[l[i]] * prefix[r[i]]) % m;
            printf("%d", result);
            printf("\n");
        }
        else {
            long long result = (prefix[r[i]]) % m;
            printf("%d", result);
            printf("\n");
        }
    }
    return 0;
}