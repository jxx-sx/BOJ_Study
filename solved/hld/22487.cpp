#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#define N 200001
#define pb push_back
#define INF 2020202020

using namespace std;

int n, q, ord;
int sz[N], p[N], top[N], in[N], out[N], w[N], dep[N];
vector<int> e[N], c[N];

struct Node {
    long long lmx, rmx, mx, sum, lazy;

    Node operator+(const Node &t) const {
        Node ret;
        ret.lmx = max(lmx, sum + t.lmx);
        ret.rmx = max(t.rmx, rmx + t.sum);
        ret.mx = max(max(mx, t.mx), rmx + t.lmx);
        ret.sum = sum + t.sum;
        return ret;
    }

    Node() : lmx(-INF), rmx(-INF), mx(-INF), sum(0), lazy(INF) {}
    Node(long long x) : lmx(x), rmx(x), mx(x), sum(x), lazy(INF) {}
    Node(long long x, long long sz) : lmx(max(x, sz * x)), rmx(max(x, sz * x)), mx(max(x, sz * x)), sum(sz * x), lazy(x) {}
};

struct Seg {
    Node node[N << 2];

    void push(int x, int s, int e) {
        Node &cur = node[x];
        if (cur.lazy == INF)
            return;
        node[x << 1] = Node(cur.lazy, (s + e) / 2 - s + 1);
        node[x << 1 | 1] = Node(cur.lazy, e - (s + e) / 2);
        cur.lazy = INF;
    }

    void update(int k, int d, int s, int e, int i) {
        if (s == e) {
            node[i] = Node(d);
            return;
        }
        if (k > (s + e) / 2)
            update(k, d, (s + e) / 2 + 1, e, i << 1 | 1);
        else
            update(k, d, s, (s + e) / 2, i << 1);
        node[i] = node[i << 1] + node[i << 1 | 1];
    }

    void update(int l, int r, int d, int s, int e, int i) {
        if (e < l or r < s)
            return;
        if (l <= s and e <= r) {
            node[i] = Node(d, e - s + 1);
            return;
        }
        push(i, s, e);

        update(l, r, d, s, (s + e) / 2, i << 1);
        update(l, r, d, (s + e) / 2 + 1, e, i << 1 | 1);

        node[i] = node[i << 1] + node[i << 1 | 1];
    }

    void update(int a, int b, int d) {
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]])
                swap(a, b);
            int t = top[a];
            update(in[t], in[a], d, 1, n, 1);
            a = p[t];
        }
        if (dep[a] > dep[b])
            swap(a, b);
        update(in[a], in[b], d, 1, n, 1);
    }

    Node get(int l, int r, int s, int e, int i) {
        if (e < l or r < s)
            return Node();
        if (l <= s and e <= r)
            return node[i];
        push(i, s, e);
        return get(l, r, s, (s + e) / 2, i << 1) + get(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    }

    int get(int a, int b) {
        bool left = true;
        Node l, r;
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) {
                swap(a, b);
                left = !left;
            }
            int t = top[a];
            if (left)
                l = get(in[t], in[a], 1, n, 1) + l;
            else
                r = get(in[t], in[a], 1, n, 1) + r;
            a = p[t];
        }
        if (dep[a] > dep[b]) {
            swap(a, b);
            left = !left;
        }
        if (left)
            r = get(in[a], in[b], 1, n, 1) + r;
        else
            l = get(in[a], in[b], 1, n, 1) + l;
        swap(l.lmx, l.rmx);
        return (l + r).mx;
    }

} tree;

void dfs(int x = 1) {
    sz[x] = 1;
    for (auto a : e[x]) {
        if (sz[a])
            continue;
        c[x].pb(a);
        dfs(a);
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
    out[x] = ord;
}

void init() {
    int a, b;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        e[a].pb(b);
        e[b].pb(a);
    }
}

void solve() {
    dfs();
    dfs1();
    dfs2();

    for (int i = 1; i <= n; i++)
        tree.update(in[i], w[i], 1, n, 1);
    int op, a, b, c;

    while (q--) {
        cin >> op >> a >> b >> c;
        if (op == 1)
            tree.update(a, b, c);
        else
            cout << tree.get(a, b) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}