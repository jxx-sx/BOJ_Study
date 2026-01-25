#include <iostream>
#include <vector>
#define pb push_back
#define N 100001

using namespace std;

int sz[N], p[N], in[N], dep[N], top[N], chk[N];
long long tree[N << 2], lazy[N << 2];
int n, m, ord;
vector<int> e[N], c[N];

void push_down(int i) {
    lazy[i << 1] += lazy[i];
    lazy[i << 1 | 1] += lazy[i];
}

void propagate(int s, int e, int i) {
    tree[i] += lazy[i] * (e - s + 1);
    if (s != e)
        push_down(i);
    lazy[i] = 0;
}

void update(int l, int r, int s, int e, int i) {
    propagate(s, e, i);
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i] += e - s + 1;
        if (s != e) {
            lazy[i << 1]++;
            lazy[i << 1 | 1]++;
        }
        return;
    }
    update(l, r, s, (s + e) / 2, i << 1);
    update(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

long long sum(int l, int r, int s, int e, int i) {
    propagate(s, e, i);
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];
    return sum(l, r, s, (s + e) / 2, i << 1) + sum(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
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

long long sum_query(int a, int b) {
    long long ret = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        ret += sum(in[st], in[a], 1, n, 1);
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    ret += sum(in[a] + 1, in[b], 1, n, 1);
    return ret;
}

void dfs(int x) {
    chk[x] = 1;
    for (auto a : e[x]) {
        if (chk[a])
            continue;
        c[x].pb(a);
        dfs(a);
    }
}

void dfs1(int x) {
    sz[x] = 1;
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
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
}

void init() {
    int a, b;
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        e[a].pb(b);
        e[b].pb(a);
    }
    dfs(1);
    dfs1(1);
    dfs2(1);
}

void solve() {
    char op;
    int u, v;
    while (m--) {
        cin >> op >> u >> v;
        if (op == 'P')
            update_query(u, v);
        else
            cout << sum_query(u, v) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}