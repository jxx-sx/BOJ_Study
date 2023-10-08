#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#define pb push_back
#define N 100001

using namespace std;

int n, m, ord, mst, sz[N], top[N], dep[N], p[N], in[N], w[N];

struct seg {
    int node[N << 2];

    void update(int k, int w, int s, int e, int i) {
        node[i] = max(node[i], w);
        if (s == e)
            return;
        if ((s + e) / 2 < k)
            update(k, w, (s + e) / 2 + 1, e, i << 1 | 1);
        else
            update(k, w, s, (s + e) / 2, i << 1);
    }

    int get(int l, int r, int s, int e, int i) {
        if (e < l or r < s)
            return 0;
        if (l <= s and e <= r)
            return node[i];
        return max(get(l, r, s, (s + e) / 2, i << 1), get(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
    }

} tree;

struct union_find {
    int p[N];

    int find_root(int x) {
        if (p[x] == x)
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

    void init() {
        for (int i = 1; i <= n; i++)
            p[i] = i;
    }
} uf;

struct Edge {
    int s, e, w;

    Edge(int s, int e, int w) : s(s), e(e), w(w) {}
    bool operator<(const Edge &T) const { return w < T.w; }
};

vector<int> c[N];
vector<pair<int, int>> e[N];
vector<Edge> edges;

map<pair<int, int>, int> mp;

void kruskal() {
    sort(edges.begin(), edges.end());
    int cnt = 0;
    for (auto a : edges) {
        if (cnt == n - 1)
            break;
        if (!uf.union_root(a.s, a.e))
            continue;
        e[a.s].pb({a.e, a.w});
        e[a.e].pb({a.s, a.w});
        mst += a.w;
        cnt++;
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
        p[a] = x;
        dep[a] = dep[x] + 1;
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

int lca(int a, int b) {
    int ret = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        ret = max(ret, tree.get(in[st], in[a], 1, n, 1));
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    ret = max(ret, tree.get(in[a] + 1, in[b], 1, n, 1));

    return ret;
}

void query() {
    int a, b;
    cin >> a >> b;
    cout << mst - lca(a, b) + mp[make_pair(a, b)] << '\n';
}

void init() {
    int a, b, w;
    cin >> n >> m;
    uf.init();
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        edges.pb(Edge(a, b, w));
        mp[make_pair(a, b)] = w;
    }
}

void solve() {
    kruskal();

    dfs();
    dfs1();
    dfs2();

    for (int i = 1; i <= n; i++)
        tree.update(in[i], w[i], 1, n, 1);

    int q;
    cin >> q;
    while (q--)
        query();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}