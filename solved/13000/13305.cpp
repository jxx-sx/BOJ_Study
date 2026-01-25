#include <algorithm>
#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

vector<pair<long long, long long>> v;
int n;

void init() {
    cin >> n;
    v.resize(n);
    for (int i = 1; i < n; i++) {
        cin >> v[i].first;
        v[i].first += v[i - 1].first;
    }
    for (auto &a : v)
        cin >> a.second;
}

void solve() {
    long long ans = v.back().first * v[0].second;
    long long last = v[0].second;
    for (int i = 1; i < n; i++) {
        if (v[i].second < last) {
            ans -= (last - v[i].second) * (v.back().first - v[i].first);
            last = v[i].second;
        }
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