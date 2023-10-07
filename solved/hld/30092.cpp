#include <iostream>
#include <vector>

#define pb push_back
#define N 100001

using namespace std;

int n, q, ord, sz[N], p[N], top[N], dep[N], in[N];
vector<int> c[N], e[N];

struct Seg {
    int node[400000];
    int lazy[400000];

    void push(int i) {
        if (!lazy[i])
            return;
        lazy[i << 1 | 1] = lazy[i << 1] = node[i << 1 | 1] = node[i << 1] = lazy[i];
        lazy[i] = 0;
    }

    void update(int l, int r, int k, int s, int e, int i) {
        if (e < l or r < s)
            return;
        if (l <= s and e <= r) {
            lazy[i] = node[i] = k;
            return;
        }
        push(i);
        update(l, r, k, s, (s + e) / 2, i << 1);
        update(l, r, k, (s + e) / 2 + 1, e, i << 1 | 1);
        node[i] = max(node[i << 1], node[i << 1 | 1]);
    }

    int get(int l, int r, int s, int e, int i) {

        if (e < l or r < s)
            return 0;
        if (l <= s and e <= r)
            return node[i];
        push(i);
        return max(get(l, r, s, (s + e) / 2, i << 1), get(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
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
    int a, b, mx = 0;
    cin >> a >> b;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        tree.update(in[st], in[a], i, 1, n, 1);
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    tree.update(in[a] + 1, in[b], i, 1, n, 1);

    cin >> a >> b;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        mx = max(mx, tree.get(in[st], in[a], 1, n, 1));
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);

    mx = max(mx, tree.get(in[a] + 1, in[b], 1, n, 1));
    cout << (mx == i ? "NO\n" : "YES\n");
}

void init() {
    int a, b;
    cin >> n >> q;
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

    for (int i = 1; i <= q; i++)
        query(i);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}