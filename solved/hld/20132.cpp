#include <algorithm>
#include <iostream>
#include <vector>
#define N 100001
#define inf 1010101010
#define pb push_back

using namespace std;

struct Edge {
    int s, e, w;
    bool operator<(const Edge &t) const { return w < t.w; }
} edges[300000];
long long mst;
int u_p[N], dep[N], top[N], in[N], sz[N], p[N];
pair<int, int> tree[N << 2], lazy[N << 2];
int n, m, ord;
vector<int> c[N], e[N], mst_e, non_e;

void push_down(int i) {
    if (lazy[i].first != inf or lazy[i].second != inf) {
        lazy[i << 1].first = min(lazy[i << 1].first, lazy[i].first);
        lazy[i << 1].second = min(lazy[i << 1].second, lazy[i].second);
        lazy[i << 1 | 1].first = min(lazy[i << 1 | 1].first, lazy[i].first);
        lazy[i << 1 | 1].second = min(lazy[i << 1 | 1].second, lazy[i].second);
        tree[i << 1].first = min(tree[i << 1].first, lazy[i].first);
        tree[i << 1].second = min(tree[i << 1].second, lazy[i].second);
        tree[i << 1 | 1].first = min(tree[i << 1 | 1].first, lazy[i].first);
        tree[i << 1 | 1].second = min(tree[i << 1 | 1].second, lazy[i].second);
        lazy[i] = {inf, inf};
    }
}

void tree_init(int s, int e, int i) {
    lazy[i] = tree[i] = {inf, inf};
    if (s == e)
        return;
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
}

void update(int l, int r, int w, int s, int e, int i) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        if (w % 2) {
            tree[i].first = min(tree[i].first, w);
            lazy[i].first = min(lazy[i].first, w);
        } else {
            tree[i].second = min(tree[i].second, w);
            lazy[i].second = min(lazy[i].second, w);
        }
        return;
    }
    push_down(i);
    update(l, r, w, s, (s + e) / 2, i << 1);
    update(l, r, w, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i].first = min(tree[i << 1].first, tree[i << 1 | 1].first);
    tree[i].second = min(tree[i << 1].second, tree[i << 1 | 1].second);
}

pair<int, int> get(int k, int s, int e, int i) {
    if (s == e)
        return tree[i];
    push_down(i);
    if (k > (s + e) / 2)
        return get(k, (s + e) / 2 + 1, e, i << 1 | 1);
    return get(k, s, (s + e) / 2, i << 1);
}

int find_root(int x) {
    if (u_p[x] == x)
        return x;
    return u_p[x] = find_root(u_p[x]);
}

bool union_root(int i) {
    int a = find_root(edges[i].s);
    int b = find_root(edges[i].e);
    if (a == b)
        return false;
    u_p[a] = b;
    return true;
}

void kruskal() {
    for (int i = 0; i < m; i++)
        if (union_root(i)) {
            mst_e.pb(i);
            mst += edges[i].w;
            e[edges[i].s].pb(edges[i].e);
            e[edges[i].e].pb(edges[i].s);
        } else
            non_e.pb(i);
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
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
}

void query(int i) {
    int a = edges[i].s;
    int b = edges[i].e;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        update(in[st], in[a], edges[i].w, 1, n, 1);
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    update(in[a] + 1, in[b], edges[i].w, 1, n, 1);
}

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        u_p[i] = i;
    for (int i = 0; i < m; i++)
        cin >> edges[i].s >> edges[i].e >> edges[i].w;
    tree_init(1, n, 1);
    sort(edges, edges + m);
    kruskal();
    dfs(1);
    dfs1(1);
    dfs2(1);
}

void solve() {
    int cur = inf;
    for (auto a : non_e)
        query(a);
    for (auto a : mst_e) {
        pair<int, int> tmp = get((dep[edges[a].s] > dep[edges[a].e] ? in[edges[a].s] : in[edges[a].e]), 1, n, 1);
        int tmp2 = edges[a].w % 2 ? tmp.second : tmp.first;
        if (tmp2 != inf)
            cur = min(cur, tmp2 - edges[a].w);
    }

    if (mst % 2)
        cout << mst << ' ' << (cur == inf ? -1 : mst + cur);
    else
        cout << (cur == inf ? -1 : mst + cur) << ' ' << mst;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}