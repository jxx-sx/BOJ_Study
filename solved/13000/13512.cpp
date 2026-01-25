#include <iostream>
#include <vector>
#define pb push_back

using namespace std;

int n, m;
int ord;
int tree[404040];
int chk[101010];
int sz[101010];
int p[101010];
int dep[101010];
int top[101010];
int in[101010];
int rev[101010];
vector<int> e[101010];
vector<int> c[101010];

int tree_query(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];
    int ll = tree_query(l, r, s, (s + e) / 2, i << 1);
    int rr = tree_query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    return ll ? ll : rr;
}

void update(int k, int s, int e, int i) {
    if (s == k and k == e) {
        tree[i] = tree[i] ? 0 : s;
        return;
    }
    if (k > (s + e) / 2)
        update(k, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        update(k, s, (s + e) / 2, i << 1);

    tree[i] = tree[i << 1] ? tree[i << 1] : tree[i << 1 | 1];
    return;
}

int query(int a) {
    int ret = 0;
    while (top[a]) {
        int st = top[a];
        int q = tree_query(in[st], in[a], 1, n, 1);
        a = p[st];
        if (q)
            ret = q;
    }
    int q = tree_query(1, in[a], 1, n, 1);
    if (q)
        ret = q;
    return ret ? rev[ret] : -1;
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
    rev[ord] = x;
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
}

void init() {
    int a, b;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        e[a].pb(b);
        e[b].pb(a);
    }
    cin >> m;
    dfs(1);
    dfs1(1);
    dfs2(1);
}

void solve() {
    int op, k;
    while (m--) {
        cin >> op >> k;
        if (op == 1)
            update(in[k], 1, n, 1);
        else
            cout << query(k) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}