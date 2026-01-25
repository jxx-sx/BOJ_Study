#include <cmath>
#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

bool arr[1'000'001];
ll mn, mx;

void init() { cin >> mn >> mx; }

void solve() {
    ll cnt = mx - mn + 1;
    for (ll i = 2; i * i <= mx; i++) {
        for (ll j = (mn + (i * i) - 1) / (i * i) * (i * i); j <= mx; j += i * i) {
            if (!arr[j - mn]) {
                arr[j - mn] = true;
                cnt--;
            }
        }
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    init();
    solve();

    return 0;
}