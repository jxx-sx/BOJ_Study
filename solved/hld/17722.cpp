#include <iostream>
#include <vector>
#define N 100001
#define pb push_back

using namespace std;

struct Query {
    int s, e, q;
    Query() : s(0), e(0), q(0) {}
    Query(int s, int e, int q) : s(s), e(e), q(q) {}
};

int n, q, ord, u_p[N], sz[N], top[N], p[N], in[N], dep[N], tree[N << 2], lazy[N << 2];
vector<int> c[N], e[N];
vector<Query> v;

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

void push(int s, int e, int i) {
    if (lazy[i]) {
        int m = (s + e) / 2;
        lazy[i << 1] = lazy[i << 1 | 1] = 1;
        tree[i << 1] = m - s + 1;
        tree[i << 1 | 1] = e - m;
        lazy[i] = 0;
    }
}

void update(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i] = e - s + 1;
        lazy[i] = 1;
        return;
    }
    push(s, e, i);
    update(l, r, s, (s + e) / 2, i << 1);
    update(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

int get(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];
    push(s, e, i);
    return get(l, r, s, (s + e) / 2, i << 1) + get(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

void update_query(int a, int b) {
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        update(in[st], in[a], 1, n, 1);
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    update(in[a] + 1, in[b], 1, n, 1);
}

int get_query(int a, int b) {
    int ret = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        ret += in[a] - in[st] + 1 - get(in[st], in[a], 1, n, 1);
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    ret += in[b] - in[a] - get(in[a] + 1, in[b], 1, n, 1);
    return ret;
}

void init() {
    int t, a, b;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        u_p[i] = i;
    while (q--) {
        cin >> t >> a >> b;
        if (t == 1) {
            if (union_root(a, b)) {
                e[a].pb(b);
                e[b].pb(a);
            } else
                v.pb(Query(a, b, 1));
        } else
            v.pb(Query(a, b, find_root(a) == find_root(b) ? 2 : 0));
    }

    for (int i = 2; i <= n; i++) {
        a = find_root(1);
        b = find_root(i);
        if (a == b)
            continue;
        u_p[a] = b;
        e[1].pb(i);
    }

    dfs(1);
    dfs1(1);
    dfs2(1);
}

void solve() {
    for (auto a : v) {
        if (a.q == 1) {
            update_query(a.s, a.e);
            continue;
        }
        if (a.q == 2) {
            cout << get_query(a.s, a.e) << '\n';
            continue;
        }
        cout << "-1\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}