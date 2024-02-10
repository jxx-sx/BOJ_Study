#include <algorithm>
#include <iostream>
#include <vector>

#define N 100001
#define INF 10000001

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct UnionFind {
    int p[N];

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

    UnionFind() {
        for (int i = 1; i < N; i++)
            p[i] = i;
    }
} union_find;

struct Edge {
    long long s, e, w;
    bool mst;
    Edge(long long s = 0, long long e = 0, long long w = 0) : s(s), e(e), w(w), mst(false) {}
    bool operator<(const Edge &t) const { return w < t.w; }
};

int n, m, ord;
int p[N], sz[N], dep[N], top[N], in[N], rev[N];
long long sum, ans;
long long w[N];
long long tree[N << 2];
bool lz[N << 2];
vector<Edge> edges, mst;
vector<int> e[N], c[N];

void kruskal() {
    sort(edges.begin(), edges.end());
    for (auto &a : edges) {
        if (!union_find.union_root(a.s, a.e))
            continue;
        a.mst = true;
        mst.push_back(a);
        e[a.s].push_back(a.e);
        e[a.e].push_back(a.s);
        sum += a.w;
    }
}

void dfs(int x = 1) {
    sz[x] = 1;
    for (auto a : e[x]) {
        if (sz[a])
            continue;
        c[x].push_back(a);
        p[a] = x;
        dep[a] = dep[x] + 1;
        dfs(a);
    }
}

void dfs1(int x = 1) {
    for (auto &a : c[x]) {
        dfs1(a);
        sz[x] += sz[a];
        if (sz[a] > sz[c[x][0]])
            swap(a, c[x][0]);
    }
}

void dfs2(int x = 1) {
    in[x] = ++ord;
    rev[in[x]] = x;
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
}

void push(int i) {
    if (!lz[i])
        return;
    for (auto a : {i << 1, i << 1 | 1}) {
        tree[a] = INF;
        lz[a] = true;
    }
    lz[i] = false;
}

void tree_init(int s = 1, int e = n, int i = 1) {
    if (s == e) {
        tree[i] = w[rev[s]];
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
}

long long get(int l, int r, int s = 1, int e = n, int i = 1) {
    if (e < l or r < s or tree[i] == INF)
        return INF;
    if (l <= s and e <= r) {
        long long ret = tree[i];
        tree[i] = INF;
        lz[i] = true;
        return ret;
    }
    push(i);
    long long ll = get(l, r, s, (s + e) / 2, i << 1);
    long long rr = get(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
    return min(ll, rr);
}

void query(int a, int b, long long d) {
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        long long tmp = get(in[top[a]], in[a]);
        if (tmp != INF)
            ans = max(ans, d - tmp);
        a = p[top[a]];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    long long tmp = get(in[a] + 1, in[b]);
    if (tmp != INF)
        ans = max(ans, d - tmp);
}

void init() {
    cin >> n >> m;
    edges.resize(m);
    for (auto &a : edges)
        cin >> a.s >> a.e >> a.w;
}

void solve() {
    kruskal();
    dfs();
    dfs1();
    dfs2();
    for (auto a : mst)
        w[p[a.s] == a.e ? a.s : a.e] = a.w;
    tree_init();

    for (auto a : edges) {
        if (a.mst)
            continue;
        query(a.s, a.e, a.w);
    }
    cout << sum + ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}