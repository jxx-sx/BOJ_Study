#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m, tree[2020];
vector<pair<int, int>> v;

void update(int x) {
    while (x <= n) {
        tree[x] += 1;
        x += x & -x;
    }
}

int sum(int x) {
    int ret = 0;
    while (x) {
        ret += tree[x];
        x -= x & -x;
    }
    return ret;
}

void init() {
    cin >> n >> m;
    v.resize(m);
    for (auto &a : v)
        cin >> a.first >> a.second;
    sort(v.begin(), v.end());
}

void solve() {
    long long ans = 0;
    while (v.size()) {
        ans += sum(v.back().second - 1);
        update(v.back().second);
        v.pop_back();
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