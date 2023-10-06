#include <algorithm>
#include <iostream>
#include <vector>
#define N 50001
#define inf 1000000
#define pb push_back

using namespace std;

struct Edge {
    int s, e, w;
    bool mst;
    Edge(int s, int e, int w) : s(s), e(e), w(w), mst(false) {}

    bool operator<(const Edge &t) const { return w < t.w; }
};

struct Node {
    int mn1, mn2;

    void update(int x) {
        if (x == mn1 or x == mn2)
            return;
        if (x < mn1) {
            mn2 = mn1;
            mn1 = x;
            return;
        }
        if (x < mn2)
            mn2 = x;
    }

    Node() : mn1(inf), mn2(inf) {}
    Node(int mn1, int mn2) : mn1(mn1), mn2(mn2) {}
};

Node comp(Node a, Node b) {
    if (b.mn1 == a.mn1)
        return Node(a.mn1, min(a.mn2, b.mn2));
    if (a.mn1 < b.mn2)
        return Node(a.mn1, min(a.mn2, b.mn1));
    return Node(b.mn1, min(a.mn1, b.mn2));
}

struct Seg {
    Node tree[200000];
    void push(int i) {
        if (tree[i].mn1 == inf)
            return;
        tree[i << 1] = comp(tree[i << 1], tree[i]);
        tree[i << 1 | 1] = comp(tree[i << 1 | 1], tree[i]);
        tree[i] = Node();
    }

    void update(int l, int r, int w, int s, int e, int i) {
        if (e < l or r < s)
            return;
        if (l <= s and e <= r) {
            tree[i].update(w);
            return;
        }
        push(i);
        update(l, r, w, s, (s + e) / 2, i << 1);
        update(l, r, w, (s + e) / 2 + 1, e, i << 1 | 1);
    }

    Node get(int x, int s, int e, int i) {
        if (s == e)
            return tree[i];
        push(i);
        if ((s + e) / 2 < x)
            return get(x, (s + e) / 2 + 1, e, i << 1 | 1);
        return get(x, s, (s + e) / 2, i << 1);
    }
} tree;

int n, m, ord, sum, sz[N], in[N], p[N], top[N], dep[N], u_p[N], w[N];
vector<int> c[N];
vector<pair<int, int>> e[N];
vector<Edge> edges;

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

bool kruskal() {
    int cnt = 0;
    for (auto &a : edges) {
        if (union_root(a.s, a.e)) {
            e[a.s].pb({a.e, a.w});
            e[a.e].pb({a.s, a.w});
            a.mst = true;
            sum += a.w;
            cnt++;
        }
        if (cnt == n - 1)
            break;
    }
    return cnt == n - 1;
}

void query(int a, int b, int w) {
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        tree.update(in[st], in[a], w, 1, n, 1);
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    tree.update(in[a] + 1, in[b], w, 1, n, 1);
}

void init() {
    int a, b, w;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        u_p[i] = i;
    while (m--) {
        cin >> a >> b >> w;
        edges.pb(Edge(a, b, w));
    }
}

void solve() {
    sort(edges.begin(), edges.end());
    if (!kruskal()) {
        cout << -1;
        return;
    }
    dfs();
    dfs1();
    dfs2();
    for (auto a : edges) {
        if (a.mst)
            continue;
        query(a.s, a.e, a.w);
    }

    int ans = inf;

    for (int i = 1; i <= n; i++) {
        auto tmp = tree.get(in[i], 1, n, 1);
        if (tmp.mn1 == inf)
            continue;
        if (tmp.mn1 == w[i]) {
            if (tmp.mn2 == inf)
                continue;
            else
                ans = min(tmp.mn2 - w[i], ans);
        } else
            ans = min(tmp.mn1 - w[i], ans);
    }
    cout << (ans == inf ? -1 : sum + ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}