#include <algorithm>
#include <iostream>
#include <memory.h>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int tree[75001];
vector<pair<int, int>> v;
vector<int> coord;
long long ans;
int n;

void update(int x) {
    while (x <= n) {
        tree[x]++;
        x += x & -x;
    }
}

int get(int x) {
    int ret = 0;
    while (x) {
        ret += tree[x];
        x -= x & -x;
    }
    return ret;
}

void init() {
    memset(tree, 0, sizeof tree);
    v.clear();
    coord.clear();
    ans = 0;
    cin >> n;
    v.resize(n);
    for (auto &a : v) {
        cin >> a.second >> a.first;
        a.second *= -1;
        coord.push_back(a.second);
    }
    sort(v.begin(), v.end());
    sort(coord.begin(), coord.end());
}

void solve() {
    for (auto a : v) {
        int x = lower_bound(coord.begin(), coord.end(), a.second) - coord.begin() + 1;
        ans += get(x);
        update(x);
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