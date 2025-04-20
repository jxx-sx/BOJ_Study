#include <algorithm>
#include <iostream>
#include <vector>

#define N 1
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

vector<ll> v;
int t;
void init() {
    v.pb(0);
    for (ll i = 1; i <= 75555; i++) {
        v.pb(v.back() + i);
        v.pb(v.back() + i);
    }
    cin >> t;
}

void solve() {
    ll st, ed;
    while (t--) {
        cin >> st >> ed;
        cout << lower_bound(v.begin(), v.end(), ed - st) - v.begin() << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    init();
    solve();

    return 0;
}