#include <iostream>
#include <numeric>

#define MOD 1000000007

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int m;
long long n, s;
long long ans;

long long get(long long x) {
    int i = MOD - 2;
    long long ret = 1;
    while (i) {
        if (i & 1) {
            ret *= x;
            ret %= MOD;
        }
        x = x * x % MOD;
        i >>= 1;
    }
    return ret;
}

void init() { cin >> m; }

void solve() {
    while (m--) {
        cin >> n >> s;
        int tmp = gcd(n, s);
        n /= tmp;
        s /= tmp;
        ans += s * get(n) % MOD;
        ans %= MOD;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}