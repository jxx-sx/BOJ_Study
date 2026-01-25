#include <algorithm>
#include <iostream>
#include <vector>
#define N 100001
#define M 300001
#define inf 1000000001
#define pb push_back

using namespace std;

struct Edge {
    int s, e, i;
    long long w;
    Edge() : s(0), e(0), w(0), i(0){};
    Edge(const Edge &t) : s(t.s), e(t.e), w(t.w), i(t.i) {}
    bool operator<(const Edge &t) const { return w < t.w; }
} edge[M];

int union_p[N], sz[N], p[N], dep[N], in[N], top[N];
int n, m, ord;
long long ans[M], tree[N << 2], lazy[N << 2];
long long cur;
vector<int> non_mst, mst, e[N], c[N];

void tree_init(int s, int e, int i) {
    lazy[i] = tree[i] = inf;
    if (s == e)
        return;
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
}

void push_down(int i) {
    if (lazy[i] != inf) {
        lazy[i << 1] = min(lazy[i << 1], lazy[i]);
        lazy[i << 1 | 1] = min(lazy[i << 1 | 1], lazy[i]);
        tree[i << 1] = min(tree[i << 1], lazy[i]);
        tree[i << 1 | 1] = min(tree[i << 1 | 1], lazy[i]);
        lazy[i] = inf;
    }
}

void update(int l, int r, long long w, int s, int e, int i) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i] = min(tree[i], w);
        lazy[i] = min(lazy[i], w);
        return;
    }
    push_down(i);
    update(l, r, w, s, (s + e) / 2, i << 1);
    update(l, r, w, (s + e) / 2 + 1, e, i << 1 | 1);
}

long long get_min(int k, int s, int e, int i) {
    if (s == e)
        return tree[i];
    push_down(i);
    if (k > (s + e) / 2)
        return get_min(k, (s + e) / 2 + 1, e, i << 1 | 1);
    return get_min(k, s, (s + e) / 2, i << 1);
}

int find_root(int x) {
    if (union_p[x] == x)
        return x;
    return union_p[x] = find_root(union_p[x]);
}

bool union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);

    if (a == b)
        return false;
    union_p[a] = b;
    return true;
}

void kruskal() {
    for (int i = 0; i < m; i++) {
        if (mst.size() == n - 1 or !union_root(edge[i].s, edge[i].e)) {
            non_mst.pb(i);
            continue;
        }
        mst.pb(i);
        cur += edge[i].w;
        e[edge[i].s].pb(edge[i].e);
        e[edge[i].e].pb(edge[i].s);
    }
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

void query(Edge *t) {
    int a = t->s;
    int b = t->e;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        update(in[st], in[a], t->w, 1, n, 1);
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    update(in[a] + 1, in[b], t->w, 1, n, 1);
}

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        union_p[i] = i;
    for (int i = 0; i < m; i++) {
        cin >> edge[i].s >> edge[i].e >> edge[i].w;
        edge[i].i = i;
    }
    sort(edge, edge + m);
    kruskal();
    dfs(1);
    dfs1(1);
    dfs2(1);
    tree_init(1, n, 1);
}

void solve() {
    for (auto a : non_mst) {
        query(edge + a);
        ans[edge[a].i] = cur;
    }
    for (auto a : mst) {
        long long tmp = get_min(in[dep[edge[a].s] > dep[edge[a].e] ? edge[a].s : edge[a].e], 1, n, 1);
        ans[edge[a].i] = tmp == inf ? -1 : cur + tmp - edge[a].w;
    }

    for (int i = 0; i < m; i++)
        cout << ans[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}