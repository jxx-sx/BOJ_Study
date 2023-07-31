#include <algorithm>
#include <iostream>
#include <vector>
#define pb push_back
#define N 100001

using namespace std;

struct Node {
    int d;
    Node *l, *r;
    Node() : d(0), l(nullptr), r(nullptr) {}
} tree[N];

int sz[N], p[N], top[N], in[N], dep[N], w[N];
int n, m, ord;
vector<int> e[N], c[N], v;

void tree_init(int s, int e, Node *cur) {
    if (s == e)
        return;
    cur->l = new Node();
    cur->r = new Node();
    tree_init(s, (s + e) / 2, cur->l);
    tree_init((s + e) / 2 + 1, e, cur->r);
}

void tree_init1(int k, int s, int e, Node *cur, Node *before) {
    cur->d = before->d + 1;
    if (s == e)
        return;
    if (k > (s + e) / 2) {
        cur->l = before->l;
        cur->r = new Node();
        tree_init1(k, (s + e) / 2 + 1, e, cur->r, before->r);
    } else {
        cur->l = new Node();
        cur->r = before->r;
        tree_init1(k, s, (s + e) / 2, cur->l, before->l);
    }
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
    tree_init1(w[x], 0, n - 1, tree + in[x], tree + in[p[x]]);
    for (auto a : c[x]) {
        top[a] = a == c[x][0] ? top[x] : a;
        dfs2(a);
    }
}

int lca(int a, int b) {
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]])
            swap(a, b);
        a = p[top[a]];
    }
    return (dep[a] < dep[b] ? a : b);
}

int query(int k, int s, int e, Node *a, Node *b, Node *anc1, Node *anc2) {
    if (s == e)
        return s;
    int l = a->l->d + b->l->d - anc1->l->d - anc2->l->d;
    if (k > l)
        return query(k - l, (s + e) / 2 + 1, e, a->r, b->r, anc1->r, anc2->r);
    return query(k, s, (s + e) / 2, a->l, b->l, anc1->l, anc2->l);
}

void init() {
    int a, b;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        v.push_back(w[i]);
    }
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        e[a].pb(b);
        e[b].pb(a);
    }
    sort(v.begin(), v.end());
    for (int i = 1; i <= n; i++)
        w[i] = lower_bound(v.begin(), v.end(), w[i]) - v.begin();
    tree_init(0, n - 1, tree);
    dfs(1);
    dfs1(1);
    dfs2(1);
}

void solve() {
    int a, b, k;
    while (m--) {
        cin >> a >> b >> k;
        int anc = lca(a, b);
        cout << v[query(k, 0, n - 1, tree + in[a], tree + in[b], tree + in[anc], tree + in[p[anc]])] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}