#include <iostream>
#include <vector>
#define pb push_back
#define N 100001

using namespace std;

int tree[N], sz[N], dep[N], p[N], in[N], top[N], w[N];
int n, q, ord;
vector<int> e[N], c[N];

void update(int i, int d) {
    while (i <= n) {
        tree[i] ^= d;
        i += i & -i;
    }
}

int sum(int i) {
    int ret = 0;
    while (i) {
        ret ^= tree[i];
        i -= i & -i;
    }
    return ret;
}

int query(int a, int b) {
    int ret = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        int st = top[a];
        ret ^= sum(in[a]) ^ sum(in[st] - 1);
        a = p[st];
    }
    if (dep[a] > dep[b])
        swap(a, b);
    ret ^= sum(in[b]) ^ sum(in[a] - 1);
    return ret;
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
    ord++;
    in[x] = ord;
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
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
    dfs(1);
    dfs1(1);
    dfs2(1);
    for (int i = 1; i <= n; i++)
        update(in[i], w[i]);
}

void solve() {
    int op, i, j;
    while (q--) {
        cin >> op >> i >> j;
        if (op == 1) {
            update(in[i], w[i] ^ j);
            w[i] = j;
        } else
            cout << query(i, j) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}