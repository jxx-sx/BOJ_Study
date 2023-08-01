#include <iostream>
#include <vector>
#define N 100001
#define pb push_back
#define emp 10001

using namespace std;

struct Node {
    long long l, r, m, s;
    Node() : l(0), r(0), m(0), s(0) {}
} tree[N << 2];

int sz[N], p[N], dep[N], top[N], in[N], rev[N];
long long w[N], lazy[N << 2];
int n, m, ord;
vector<int> v[N], c[N];

void push_down(int s, int e, int i) {
    if (lazy[i] != emp) {
        lazy[i << 1] = lazy[i << 1 | 1] = lazy[i];

        tree[i << 1].s = lazy[i] * ((s + e) / 2 - s + 1);
        tree[i << 1].l = tree[i << 1].r = tree[i << 1].m = tree[i << 1].s > 0 ? tree[i << 1].s : 0;

        tree[i << 1 | 1].s = lazy[i] * (e - (s + e) / 2);
        tree[i << 1 | 1].l = tree[i << 1 | 1].r = tree[i << 1 | 1].m = tree[i << 1 | 1].s > 0 ? tree[i << 1 | 1].s : 0;

        lazy[i] = emp;
    }
}

void tree_init(int s, int e, int i) {
    lazy[i] = emp;
    if (s == e) {
        tree[i].s = w[rev[s]];
        tree[i].m = tree[i].r = tree[i].l = tree[i].s > 0 ? tree[i].s : 0;
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i].l = max(tree[i << 1].l, tree[i << 1].s + tree[i << 1 | 1].l);
    tree[i].r = max(tree[i << 1].r + tree[i << 1 | 1].s, tree[i << 1 | 1].r);
    tree[i].m = max(max(tree[i << 1].m, tree[i << 1 | 1].m), tree[i << 1].r + tree[i << 1 | 1].l);
    tree[i].s = tree[i << 1].s + tree[i << 1 | 1].s;
}

void update(int l, int r, int d, int s, int e, int i) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i].s = (long long)(e - s + 1) * d;
        tree[i].l = tree[i].r = tree[i].m = d > 0 ? tree[i].s : 0;
        lazy[i] = d;
        return;
    }
    push_down(s, e, i);
    update(l, r, d, s, (s + e) / 2, i << 1);
    update(l, r, d, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i].l = max(tree[i << 1].l, tree[i << 1].s + tree[i << 1 | 1].l);
    tree[i].r = max(tree[i << 1].r + tree[i << 1 | 1].s, tree[i << 1 | 1].r);
    tree[i].m = max(max(tree[i << 1].m, tree[i << 1 | 1].m), tree[i << 1].r + tree[i << 1 | 1].l);
    tree[i].s = tree[i << 1].s + tree[i << 1 | 1].s;
}

Node sum(int l, int r, int s, int e, int i) {
    Node rtn;
    if (e < l or r < s)
        return rtn;
    if (l <= s and e <= r)
        return tree[i];
    push_down(s, e, i);
    Node ll = sum(l, r, s, (s + e) / 2, i << 1);
    Node rr = sum(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    rtn.l = max(ll.l, ll.s + rr.l);
    rtn.r = max(ll.r + rr.s, rr.r);
    rtn.m = max(max(ll.m, rr.m), ll.r + rr.l);
    rtn.s = ll.s + rr.s;
    return rtn;
}

void dfs(int x) {
    sz[x] = 1;
    for (auto a : v[x]) {
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
    ord++;
    in[x] = ord;
    rev[ord] = x;
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
}

int query(int a, int b) {
    Node l, r, tmp;
    bool left = true;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) {
            swap(a, b);
            left = !left;
        }
        int st = top[a];
        tmp = sum(in[st], in[a], 1, n, 1);
        if (left) {
            l.m = max(max(l.m, tmp.m), l.r + tmp.r);
            l.l = max(l.l, l.s + tmp.r);
            l.r = max(tmp.l, tmp.s + l.r);
            l.s += tmp.s;
        } else {
            r.m = max(max(r.m, tmp.m), tmp.r + r.l);
            r.l = max(tmp.l, tmp.s + r.l);
            r.r = max(r.r, tmp.r + r.s);
            r.s += tmp.s;
        }
        a = p[st];
    }
    if (dep[a] > dep[b]) {
        swap(a, b);
        left = !left;
    }
    tmp = sum(in[a], in[b], 1, n, 1);
    if (left) {
        l.m = max(max(l.m, tmp.m), l.r + tmp.l);
        l.l = max(l.l, l.s + tmp.l);
        l.r = max(tmp.r, tmp.s + l.r);
        l.s += tmp.s;
    } else {
        r.m = max(max(r.m, tmp.m), tmp.l + r.l);
        r.l = max(tmp.r, tmp.s + r.l);
        r.r = max(r.r, tmp.l + r.s);
        r.s += tmp.s;
    }
    return max(max(l.m, r.m), l.r + r.l);
}

void update_query(int a, int b, int d) {
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        update(in[st], in[a], d, 1, n, 1);
        a = p[st];
    }

    if (dep[a] > dep[b])
        swap(a, b);
    update(in[a], in[b], d, 1, n, 1);
}

void init() {
    int s, e;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 0; i < n - 1; i++) {
        cin >> s >> e;
        v[s].pb(e);
        v[e].pb(s);
    }
    cin >> m;
    dfs(1);
    dfs1(1);
    dfs2(1);
    // tree_init(1, n, 1);
    for (int i = 1; i <= n; i++)
        update(in[i], in[i], w[i], 1, n, 1);
}

void solve() {
    int op, a, b, k;
    while (m--) {
        cin >> op >> a >> b;
        if (op == 1)
            cout << query(a, b) << '\n';
        else {
            cin >> k;
            update_query(a, b, k);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}