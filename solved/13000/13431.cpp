#include <iostream>
#include <map>
#include <vector>

#define N 100000
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, q, ord;
int _sz[N], _p[N], sub_sz[N];
int sz[N], p[N], top[N], dep[N], in[N];
long long dist[N], arr[N];
map<int, long long> sub_dist[N];
vector<pair<int, int>> e[N], c[N];
bool blue[N], visited[N];

void dfs(int x = 0) {
    sz[x] = 1;
    for (auto [a, w] : e[x]) {
        if (sz[a])
            continue;
        p[a] = x;
        dep[a] = dep[x] + 1;
        c[x].pb({a, w});
        dfs(a);
    }
}

void dfs1(int x = 0) {
    for (auto &a : c[x]) {
        dfs1(a.first);
        sz[x] += sz[a.first];
        if (sz[a.first] > sz[c[x][0].first])
            swap(a, c[x][0]);
    }
}

void dfs2(int x = 0) {
    in[x] = ord++;
    for (auto [a, w] : c[x]) {
        top[a] = a == c[x][0].first ? top[x] : a;
        dfs2(a);
        arr[in[a]] = w;
    }
}

long long get_dist(int u, int v) {
    long long ret = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ret += arr[in[u]] - arr[in[top[u]] - 1];
        u = p[top[u]];
    }
    if (u == v)
        return ret;
    if (dep[u] < dep[v])
        swap(u, v);
    ret += arr[in[u]] - arr[in[v]];
    return ret;
}

void update(int x) {
    if (blue[x])
        return;
    blue[x] = true;
    sub_sz[x]++;
    int cur = _p[x];
    int b = x;
    while (cur != -1) {
        long long tmp = get_dist(cur, x);
        dist[cur] += tmp;
        sub_dist[cur][b] += tmp;
        sub_sz[cur]++;
        b = cur;
        cur = _p[cur];
    }
}

long long query(int x) {
    long long ret = dist[x];
    int cur = _p[x];
    int b = x;
    while (cur != -1) {
        ret += dist[cur] - sub_dist[cur][b] + get_dist(cur, x) * (sub_sz[cur] - sub_sz[b]);
        b = cur;
        cur = _p[cur];
    }
    return ret;
}

int get_size(int x, int b = -1) {
    _sz[x] = 1;
    for (auto [a, _] : e[x]) {
        if (visited[a] or a == b)
            continue;
        _sz[x] += get_size(a, x);
    }
    return _sz[x];
}

int get_centroid(int x, int b, int cnt) {
    for (auto [a, _] : e[x]) {
        if (visited[a] or a == b or (_sz[a] << 1) <= cnt)
            continue;
        return get_centroid(a, x, cnt);
    }
    return x;
}

int tree_init(int x = 0) {
    x = get_centroid(x, -1, get_size(x));
    visited[x] = true;
    for (auto [a, _] : e[x]) {
        if (visited[a])
            continue;
        _p[tree_init(a)] = x;
    }
    return x;
}

void init() {
    cin >> n >> q;
    int u, v, w;
    for (int i = 1; i < n; i++) {
        cin >> u >> v >> w;
        e[u].pb({v, w});
        e[v].pb({u, w});
    }
    _p[tree_init()] = -1;
    dfs();
    dfs1();
    dfs2();
    for (int i = 1; i < n; i++)
        arr[i] += arr[i - 1];
}

void solve() {
    int op, x;
    while (q--) {
        cin >> op >> x;
        if (op == 1)
            update(x);
        else
            cout << query(x) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}