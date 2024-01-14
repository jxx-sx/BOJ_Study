#include <algorithm>
#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

vector<pair<int, int>> v;
int n;
void init() {
    v.clear();
    cin >> n;
    v.resize(n);
    for (auto &a : v)
        cin >> a.first >> a.second;
}

void solve() {
    sort(v.begin(), v.end());
    int mn = 100001;
    int ans = 0;
    for (auto a : v) {
        if (mn > a.second)
            ans++;
        mn = min(a.second, mn);
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc;
    cin >> tc;
    while (tc--) {
        init();
        solve();
    }

    return 0;
}