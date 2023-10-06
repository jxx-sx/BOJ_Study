#include <algorithm>
#include <iostream>
#include <vector>
#define N 200001
#define pb push_back

using namespace std;

struct Edge {
    int s, e, w, i;
    bool mst;

    Edge() : s(0), e(0), w(0), i(0), mst(false) {}
    bool operator<(const Edge &t) const { return w < t.w; }
};

struct Seg {
    int tree[800000];
    void update(int k, int w, int s, int e, int i) {
        if (s == e) {
            tree[i] = w;
            return;
        }
        if ((s + e) / 2 < k)
            update(k, w, (s + e) / 2 + 1, e, i << 1 | 1);
        else
            update(k, w, s, (s + e) / 2, i << 1);
        tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
    }

    int get(int l, int r, int s, int e, int i) {
        if (l <= s and e <= r)
            return tree[i];
        if (e < l or r < s)
            return 0;
        return max(get(l, r, s, (s + e) / 2, i << 1), get(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
    }
} tree;

int n, m, ord, in[N], sz[N], p[N], dep[N], top[N], w[N], u_p[N];
long long mst, ans[N];
vector<int> c[N];
vector<pair<int, int>> e[N];
vector<Edge> edges;

int find_root(int x) {
    if (u_p[x] == x)
        return x;
    return u_p[x] = find_root(u_p[x]);
}

bool union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b)
        return false;
    u_p[a] = b;
    return true;
}

void kruskal() {
    for (auto &a : edges) {
        if (!union_root(a.s, a.e))
            continue;
        a.mst = true;
        e[a.s].pb({a.e, a.w});
        e[a.e].pb({a.s, a.w});
        mst += a.w;
    }
}

void dfs(int x = 1) {
    sz[x] = 1;
    for (auto a : e[x]) {
        if (sz[a.first])
            continue;
        c[x].pb(a.first);
        w[a.first] = a.second;
        dfs(a.first);
    }
}

void dfs1(int x = 1) {
    for (auto &a : c[x]) {
        dep[a] = dep[x] + 1;
        p[a] = x;
        dfs1(a);
        sz[x] += sz[a];
        if (sz[a] > sz[c[x][0]])
            swap(a, c[x][0]);
    }
}

void dfs2(int x = 1) {
    in[x] = ++ord;
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
}

void query(int i) {
    if (edges[i].mst) {
        ans[edges[i].i] = mst;
        return;
    }
    int a = edges[i].s;
    int b = edges[i].e;
    int tmp = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        tmp = max(tree.get(in[st], in[a], 1, n, 1), tmp);
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    tmp = max(tree.get(in[a] + 1, in[b], 1, n, 1), tmp);
    ans[edges[i].i] = mst - tmp + edges[i].w;
}

void init() {
    cin >> n >> m;
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].s >> edges[i].e >> edges[i].w;
        edges[i].i = i;
    }
    for (int i = 1; i <= n; i++)
        u_p[i] = i;
}

void solve() {
    sort(edges.begin(), edges.end());
    kruskal();
    dfs();
    dfs1();
    dfs2();
    for (int i = 1; i <= n; i++)
        tree.update(in[i], w[i], 1, n, 1);
    for (int i = 0; i < m; i++)
        query(i);
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