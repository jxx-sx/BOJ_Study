#include <algorithm>
#include <iostream>
#include <vector>

#define N 501
#define N2 250001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, m, q, c[N], p[N2];
vector<int> e[N], pbs[N2];

inline int w(int x, int y);
inline int g(int x, int y);

struct Node {
    int x, y;
    inline int w() { return ::w(x, y); }
    inline int g() { return ::g(x, y); }
    Node(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator<(const Node &t) const { return ::w(x, y) < ::w(t.x, t.y); }
} node[N2];

struct Qry {
    int x, y, l, r, ans;
} qry[N2];

inline int w(int x, int y) { return c[x] * c[y]; }
inline int g(int x, int y) {
    x--, y--;
    return x * n + y;
}

int find_root(int x) {
    if (x == p[x])
        return x;
    return p[x] = find_root(p[x]);
}

void union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b)
        return;
    p[a] = b;
}

void init() {
    int u, v;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        e[u].pb(v);
        e[v].pb(u);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> qry[i].x >> qry[i].y;
        qry[i].r = n * n - 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            node[g(i, j)].x = i;
            node[g(i, j)].y = j;
        }
    }
    sort(node, node + n * n);
}

void clear() {
    for (int i = 0; i < N2; i++) {
        p[i] = i;
        pbs[i].clear();
    }
}

void solve() {
    while (true) {
        clear();
        bool flag = true;
        for (int i = 0; i < q; i++) {
            if (qry[i].l <= qry[i].r) {
                pbs[(qry[i].l + qry[i].r) >> 1].pb(i);
                flag = false;
            }
        }
        if (flag)
            break;
        for (int i = 0; i < n * n; i++) {
            for (auto a : e[node[i].x]) {
                if (w(a, node[i].y) <= node[i].w())
                    union_root(g(a, node[i].y), node[i].g());
            }
            for (auto a : e[node[i].y]) {
                if (w(node[i].x, a) <= node[i].w()) {
                    union_root(g(node[i].x, a), node[i].g());
                }
            }

            for (auto a : pbs[i]) {
                int u = find_root(g(qry[a].x, qry[a].y));
                int v = find_root(g(qry[a].y, qry[a].x));
                if (u == v) {
                    qry[a].ans = node[i].w();
                    qry[a].r = i - 1;
                } else
                    qry[a].l = i + 1;
            }
        }
    }
    for (int i = 0; i < q; i++)
        cout << qry[i].ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}