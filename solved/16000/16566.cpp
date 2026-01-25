#include <algorithm>
#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

vector<int> v;
int p[4000000];
int n, m, k;

int find_root(int x) {
    if (x == p[x])
        return x;
    return p[x] = find_root(p[x]);
}

void union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    p[a] = b;
}

void init() {
    cin >> n >> m >> k;
    v.resize(m);
    for (auto &a : v)
        cin >> a;
    sort(v.begin(), v.end());
    for (int i = 0; i < m; i++)
        p[i] = i;
}

void solve() {
    int a;
    while (k--) {
        cin >> a;
        auto i = find_root(upper_bound(v.begin(), v.end(), a) - v.begin());
        cout << v[i] << '\n';
        union_root(i, i + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}