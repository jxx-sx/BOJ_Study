#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, m, cnt[50], ans;
vector<int> v1, v2;
priority_queue<pair<int, int>> pq;

void init() {
    cin >> n;
    v1.resize(n);
    for (auto &a : v1)
        cin >> a;
    cin >> m;
    v2.resize(m);
    for (auto &a : v2)
        cin >> a;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
}

void solve() {
    if (v1.back() < v2.back()) {
        cout << -1;
        return;
    }

    for (auto i = v2.rbegin(); i != v2.rend(); i++) {
        if (v1.size() && *i <= v1.back()) {
            pq.push({-cnt[v1.size() - 1], v1.size() - 1});
            v1.pop_back();
        }
        auto [a, b] = pq.top();
        pq.pop();
        cnt[b]++;
        pq.push({-cnt[b], b});
        ans = max(ans, cnt[b]);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);

    init();
    solve();

    return 0;
}