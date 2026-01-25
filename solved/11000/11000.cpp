#include <algorithm>
#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

vector<pair<int, int>> v;
int n;
int cur, ans;

void init() {
    int s, e;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s >> e;
        v.push_back({s, 1});
        v.push_back({e, -1});
    }
}

void solve() {
    sort(v.begin(), v.end());
    for (auto a : v) {
        ans = max(cur, ans);
        cur += a.second;
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