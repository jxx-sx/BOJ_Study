#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#define pb push_back
#define N 100001
#define INF 1000000001

using namespace std;

int sz[N], p[N], d[N], in[N], top[N], tree[N << 2], lazy[N << 2];
int n, m, ord, cnt;
vector<int> c[N], e[N];

void dfs(int x = 1) {
    sz[x] = 1;
    for (auto a : e[x]) {
        if (sz[a])
            continue;
        p[a] = x;
        d[a] = d[x] + 1;
        c[x].pb(a);
        dfs(a);
    }
}

void dfs1(int x = 1) {
    for (auto &a : c[x]) {
        dfs1(a);
        sz[x] += sz[a];
        if (sz[a] > sz[c[x][0]])
            swap(c[x][0], a);
    }
}

void dfs2(int x = 1) {
    in[x] = ++ord;
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
}

void push(int i) {
    if (!lazy[i])
        return;
    tree[i << 1] -= lazy[i];
    tree[i << 1 | 1] -= lazy[i];
    lazy[i << 1] += lazy[i];
    lazy[i << 1 | 1] += lazy[i];
    lazy[i] = 0;
}

int get(int l, int r, int s, int e, int i = 1) {
    if (e < l or r < s)
        return INF;
    if (l <= s and e <= r)
        return tree[i];
    push(i);
    return min(get(l, r, s, (s + e) / 2, i << 1), get(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
}

void update(int k, int a, int s, int e, int i) {
    tree[i] = min(tree[i], a);
    if (s == e)
        return;
    if (k > (s + e) / 2)
        update(k, a, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        update(k, a, s, (s + e) / 2, i << 1);
}

void update(int l, int r, int a, int s, int e, int i) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i] -= a;
        lazy[i] += a;
        return;
    }
    push(i);
    update(l, r, a, s, (s + e) / 2, i << 1);
    update(l, r, a, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
}

int query(int x, int y) {
    int ret = INF;
    while (top[x] != top[y]) {
        if (d[top[x]] < d[top[y]])
            swap(x, y);
        int tmp = top[x];
        ret = min(ret, get(in[tmp], in[x], 1, n));
        x = p[tmp];
    }
    if (d[x] > d[y])
        swap(x, y);
    ret = min(ret, get(in[x], in[y], 1, n));
    return ret;
}

void query(int x, int y, int w) {
    while (top[x] != top[y]) {
        if (d[top[x]] < d[top[y]])
            swap(x, y);
        int tmp = top[x];
        update(in[tmp], in[x], w, 1, n, 1);
        x = p[tmp];
    }
    if (d[x] > d[y])
        swap(x, y);
    update(in[x], in[y], w, 1, n, 1);
}

void init() {
    fill(tree, tree + (N << 2), INF);

    int u, v, a;
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        e[u].pb(v);
        e[v].pb(u);
    }

    dfs();
    dfs1();
    dfs2();

    for (int i = 1; i <= n; i++) {
        cin >> a;
        update(in[i], a, 1, n, 1);
    }
}

void solve() {
    int x, y, w;
    while (m--) {
        cin >> x >> y >> w;
        if (query(x, y) < w)
            break;

        query(x, y, w);
        cnt++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}