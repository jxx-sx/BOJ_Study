#include <iostream>
#include <set>
#include <vector>

#define pb push_back
#define N 101010

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int _sz[N], _p[N];
int sz[N], dep[N], top[N], p[N];
vector<int> e[N], c[N];
int n, m;
bool visited[N];
bool white[N];
multiset<int> dist[N];

void dfs(int x = 1) {
    sz[x] = 1;
    for (auto a : e[x]) {
        if (sz[a])
            continue;
        p[a] = x;
        c[x].pb(a);
        dfs(a);
    }
}

int dfs1(int x = 1) {
    for (auto &a : c[x]) {
        dep[a] = dep[x] + 1;
        sz[x] += dfs1(a);
        if (sz[a] > sz[c[x][0]])
            swap(a, c[x][0]);
    }
    return sz[x];
}

void dfs2(int x = 1) {
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = p[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

inline int get_dist(int u, int v) { return dep[u] + dep[v] - (dep[lca(u, v)] << 1); }

int get_sz(int x, int b = -1) {
    _sz[x] = 1;
    for (auto a : e[x]) {
        if (visited[a] or a == b)
            continue;
        _sz[x] += get_sz(a, x);
    }
    return _sz[x];
}

int get_cent(int x, int b, int size) {
    for (auto a : e[x]) {
        if (visited[a] or a == b or (_sz[a] << 1) <= size)
            continue;
        return get_cent(a, x, size);
    }
    return x;
}

int build_tree(int x = 1, int b = -1) {
    x = get_cent(x, -1, get_sz(x));
    visited[x] = true;
    for (auto a : e[x]) {
        if (visited[a])
            continue;
        _p[build_tree(a, x)] = x;
    }
    return x;
}

inline void insert(int x) {
    int cur = x;
    while (cur) {
        dist[cur].insert(get_dist(cur, x));
        cur = _p[cur];
    }
}

inline void erase(int x) {
    int cur = x;
    while (cur) {
        dist[cur].erase(dist[cur].find(get_dist(cur, x)));
        cur = _p[cur];
    }
}

void update(int x) {
    white[x] ^= 1;
    if (white[x])
        insert(x);
    else
        erase(x);
}

int query(int x) {
    int cur = x;
    int ret = N;
    while (cur) {
        if (!dist[cur].empty())
            ret = min(ret, *dist[cur].begin() + get_dist(cur, x));
        cur = _p[cur];
    }
    return ret != N ? ret : -1;
}

void init() {
    int u, v;
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        e[u].pb(v);
        e[v].pb(u);
    }
    cin >> m;
}

void solve() {
    build_tree();
    dfs();
    dfs1();
    dfs2();

    int op, v;
    while (m--) {
        cin >> op >> v;
        if (op == 1)
            update(v);
        else
            cout << query(v) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}