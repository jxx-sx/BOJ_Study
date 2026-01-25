#include <algorithm>
#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

vector<int> v, dp;
int n;

void init() {
    cin >> n;
    v.resize(n);
    for (auto &a : v)
        cin >> a;
}

void solve() {
    dp.push_back(v.front());
    for (int i = 1; i < v.size(); i++) {
        if (dp.back() < v[i]) {
            dp.push_back(v[i]);
            continue;
        }
        *lower_bound(dp.begin(), dp.end(), v[i]) = v[i];
    }
    cout << dp.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}