#include <iostream>
#include <queue>
#include <stack>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;
ll n;

void init() { cin >> n; }

void solve() {
    ll lo = 1, hi = 1750000000;
    ll ans = 0;
    while (lo <= hi) {
        ll mi = (lo + hi) >> 1;
        if (n <= mi * (mi - 1) / 2 * 6 + 1) {
            ans = mi;
            hi = mi - 1;
        } else
            lo = mi + 1;
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