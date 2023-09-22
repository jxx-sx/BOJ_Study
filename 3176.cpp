#include <iostream>
#include <vector>
#define pb push_back
#define N 100001

using namespace std;

int n, m, ord;
int dep[N], p[N], in[N], top[N], sz[N], arr[N];
vector<pair<int, int>> e[N];
vector<int> c[N];

struct Node {
    int mx, mn;

    void update(int d) {
        mx = max(mx, d);
        mn = min(mn, d);
    }
    Node() : mx(0), mn(1010101) {}
    Node(int mx, int mn) : mx(mx), mn(mn) {}
};

Node comp(Node a, Node b) { return Node(max(a.mx, b.mx), min(a.mn, b.mn)); }

struct seg {
    Node tree[400000];
    void update(int k, int d, int s, int e, int i) {
        tree[i].update(d);

        if (s == e)
            return;
        if (k > (s + e) / 2)
            update(k, d, (s + e) / 2 + 1, e, i << 1 | 1);
        else
            update(k, d, s, (s + e) / 2, i << 1);
    }

    Node query(int l, int r, int s, int e, int i) {
        if (e < l or r < s)
            return Node();
        if (l <= s and e <= r)
            return tree[i];

        return comp(query(l, r, s, (s + e) / 2, i << 1), query(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
    }
} tree;

Node Query(int a, int b) {
    Node rtn = Node();

    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        rtn = comp(rtn, tree.query(in[st], in[a], 1, n, 1));
        a = p[st];
    }
    if (top[a] > top[b])
        swap(a, b);
    rtn = comp(rtn, tree.query(in[a] + 1, in[b], 1, n, 1));
    return rtn;
}

void dfs(int x) {
    sz[x] = 1;
    for (auto a : e[x])
        if (!sz[a.first]) {
            c[x].pb(a.first);
            arr[a.first] = a.second;
            dfs(a.first);
        }
}

void dfs1(int x) {
    for (auto &a : c[x]) {
        p[a] = x;
        dep[a] = dep[x] + 1;
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

void init() {
    int a, b, w;
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> a >> b >> w;
        e[a].pb({b, w});
        e[b].pb({a, w});
    }
    cin >> m;
    dfs(1);
    dfs1(1);
    dfs2(1);
    for (int i = 1; i <= n; i++)
        tree.update(in[i], arr[i], 1, n, 1);
}

void solve() {
    int a, b;
    while (m--) {
        cin >> a >> b;
        auto tmp = Query(a, b);
        cout << tmp.mn << ' ' << tmp.mx << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}