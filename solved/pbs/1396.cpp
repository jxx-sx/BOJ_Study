#include <algorithm>
#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
int n, m, q;
struct Edge {
    int s, e, c;
    bool operator<(const Edge &t) const { return c < t.c; }
    // Edge(int s=0, int e = 0, int c = 0): s(s), e)
};
struct Query {
    int x, y, l, r, i;
    Query(int x = 0, int y = 0, int l = 0, int r = m - 1) : x(x), y(y), l(l), r(r) {}
};
struct Ans {
    int c, cnt;
    Ans() : c(-1), cnt(0) {}
} ans[100000];
vector<Edge> e;
vector<Query> query, pbs[100001];
struct UnionFind {
    int p[100001], sz[100001];

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
        sz[b] += sz[a];
    }

    UnionFind() {
        for (int i = 0; i < 100001; i++) {
            p[i] = i;
            sz[i] = 1;
        }
    }
};

void init() {
    cin >> n >> m;
    e.resize(m);
    for (auto &a : e)
        cin >> a.s >> a.e >> a.c;
    cin >> q;
    query.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> query[i].x >> query[i].y;
        query[i].i = i;
    }
}

void solve() {
    sort(e.begin(), e.end());
    // for (int i = 0; i < 6; i++) {
    while (true) {
        bool flag = false;
        UnionFind uf;
        for (int i = 0; i < 100001; i++)
            pbs[i].clear();
        for (auto a : query) {
            if (a.l <= a.r) {
                pbs[(a.l + a.r) >> 1].push_back(a);
                flag = true;
            }
        }

        if (!flag)
            break;
        for (int i = 0; i < m; i++) {
            uf.union_root(e[i].s, e[i].e);
            for (auto a : pbs[i]) {
                if (uf.find_root(a.x) == uf.find_root(a.y)) {
                    ans[a.i].c = e[i].c;
                    ans[a.i].cnt = uf.sz[uf.find_root(a.x)];
                    query[a.i].r = i - 1;
                } else
                    query[a.i].l = i + 1;
            }
        }
    }

    for (int i = 0; i < q; i++) {
        if (ans[i].c == -1)
            cout << -1 << '\n';
        else
            cout << ans[i].c << ' ' << ans[i].cnt << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}