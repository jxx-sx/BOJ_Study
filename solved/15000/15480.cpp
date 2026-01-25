#include <iostream>
#include <vector>
#define N 100001
#define pb push_back

using namespace std;

int n, m, sz[N], p[N], top[N], dep[N];
vector<int> c[N], e[N];

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
        p[a] = x;
        dep[a] = dep[x] + 1;
        dfs1(a);
        sz[x] += sz[a];
        if (sz[a] > sz[c[x][0]])
            swap(a, c[x][0]);
    }
}

void dfs2(int x) {
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
}

int get_lca(int a, int b) {
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        a = p[top[a]];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    return a;
}

int query(int r, int a, int b) {
    if (dep[a] > dep[b])
        swap(a, b);
    int ra = get_lca(r, a);
    int rb = get_lca(r, b);
    int ab = get_lca(a, b);
    int rab = get_lca(r, ab);
    if (dep[rab] < dep[ab])
        return ab;
    if (ab == a) {
        if (rb == b)
            return b;
        else
            return rb;
    }
    if (ra == ab and rb == ab)
        return ab;
    if (ra == a)
        return a;
    if (rb == b)
        return b;
    if (ra == ab)
        return rb;
    else
        return ra;
}

void init() {
    int a, b;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        e[a].pb(b);
        e[b].pb(a);
    }
    dfs(1);
    dfs1(1);
    dfs2(1);
    cin >> m;
}

void solve() {
    int r, u, v;
    while (m--) {
        cin >> r >> u >> v;
        cout << query(r, u, v) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}