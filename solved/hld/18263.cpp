#include <algorithm>
#include <iostream>
#include <vector>
#define N 101010
#define pb emplace_back
using namespace std;

int n, m, ord, sz[N], top[N], dep[N], in[N], p[N], arr[N], rev[N];
vector<int> c[N], e[N];
vector<int> tree[N << 2];

void tree_init(int s, int e, int i) {
    if (s == e) {
        tree[i].pb(arr[rev[s]]);
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i].resize(tree[i << 1].size() + tree[i << 1 | 1].size());
    merge(tree[i << 1].begin(), tree[i << 1].end(), tree[i << 1 | 1].begin(), tree[i << 1 | 1].end(), tree[i].begin());
}

bool get(int l, int r, int k, int s, int e, int i) {
    if (e < l or r < s)
        return false;
    if (l <= s and e <= r)
        return binary_search(tree[i].begin(), tree[i].end(), k);
    return get(l, r, k, s, (s + e) / 2, i << 1) || get(l, r, k, (s + e) / 2 + 1, e, i << 1 | 1);
}

void dfs(int x) {
    sz[x] = 1;
    for (auto a : e[x]) {
        if (sz[a])
            continue;
        c[x].pb(a);
        dfs(a);
    }
}

void dfs1(int x) {
    for (auto &a : c[x]) {
        dep[a] = dep[x] + 1;
        p[a] = x;
        dfs1(a);
        sz[x] += sz[a];
        if (sz[a] > sz[c[x][0]])
            swap(a, c[x][0]);
    }
}

void dfs2(int x) {
    in[x] = ++ord;
    rev[in[x]] = x;
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
}

bool query(int a, int b, int w) {
    bool ret = false;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        ret |= get(in[st], in[a], w, 1, n, 1);
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    ret |= get(in[a], in[b], w, 1, n, 1);

    return ret;
}

void init() {
    int a, b;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        e[a].pb(b);
        e[b].pb(a);
    }
    dfs(1);
    dfs1(1);
    dfs2(1);
    tree_init(1, n, 1);
}

void solve() {
    int a, b, w;
    while (m--) {
        cin >> a >> b >> w;
        cout << query(a, b, w);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}