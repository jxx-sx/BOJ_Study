#include <algorithm>
#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct E {
    int u, v, w;
    bool operator<(const E &t) const { return w < t.w; }
} arr[100000];
int p[1001];
int n, m, q, s;
vector<pair<int, int>> v[1001];

int find_root(int x) {
    if (x == p[x])
        return x;
    return p[x] = find_root(p[x]);
}

bool union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b)
        return false;
    p[a] = b;
    return true;
}

int dfs(int x, int dst, int p = 0) {
    for (auto &[a, w] : v[x]) {
        if (a == p)
            continue;
        if (a == dst)
            return w;
        int ret = dfs(a, dst, x);
        if (ret)
            return max(ret, w);
    }
    return 0;
}

void mst() {
    for (int i = 0; i < m; i++) {
        if (union_root(arr[i].u, arr[i].v)) {
            v[arr[i].u].push_back({arr[i].v, arr[i].w});
            v[arr[i].v].push_back({arr[i].u, arr[i].w});
            s += arr[i].w;
        }
    }
}

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        p[i] = i;
    for (int i = 0; i < m; i++)
        cin >> arr[i].u >> arr[i].v >> arr[i].w;
    sort(arr, arr + m);
}

void solve() {
    int u, v;
    mst();
    cin >> q;
    while (q--) {
        cin >> u >> v;
        cout << s - dfs(u, v) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    init(), solve();

    return 0;
}