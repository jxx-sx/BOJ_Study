#include <algorithm>
#include <iostream>
#include <memory.h>
#include <vector>

using namespace std;

int n, m, k;
long long tree[1001];
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
    cin >> n >> m >> k;
    v.resize(k);
    for (auto &a : v)
        cin >> a.first >> a.second;
    sort(v.begin(), v.end());
    memset(tree, 0, 8008);
}

void solve() {
    long long ans = 0;
    while (v.size()) {
        ans += sum(v.back().second - 1);
        update(v.back().second);
        v.pop_back();
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    for (int i = 1; i <= tc; i++) {
        cout << "Test case " << i << ": ";
        init();
        solve();
    }

    return 0;
}