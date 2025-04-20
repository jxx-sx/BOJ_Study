#include <iostream>
#include <vector>

#define NODE -1

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Node {
    Node *l, *r, *p;
    pair<int, int> v, mx;
    bool flip;

    Node(int v = 0, int i = NODE) : l(nullptr), r(nullptr), p(nullptr), v({v, i}), mx({v, i}), flip(false) {}

    bool is_root() { return !p or (p->l != this and p->r != this); }

    void update() {
        mx = v;
        if (l)
            mx = max(mx, l->mx);
        if (r)
            mx = max(mx, r->mx);
    }

    void rotate() {
        if (this == p->l) {
            if (r)
                r->p = p;
            p->l = r;
            r = p;
        } else {
            if (l)
                l->p = p;
            p->r = l;
            l = p;
        }
        if (!p->is_root())
            (p == p->p->l ? p->p->l : p->p->r) = this;
        auto tmp = p;
        p = tmp->p;
        tmp->p = this;
        tmp->update();
        update();
    }

    void push() {
        if (!flip)
            return;
        swap(l, r);
        if (l)
            l->flip ^= 1;
        if (r)
            r->flip ^= 1;
        flip = false;
    }
};

void splay(Node *x) {
    for (; !x->is_root(); x->rotate()) {
        if (!x->p->is_root())
            x->p->p->push();
        x->p->push();
        x->push();
        if (x->p->is_root())
            continue;
        if ((x->p->l == x) == (x->p->p->l == x->p))
            x->p->rotate();
        else
            x->rotate();
    }
    x->push();
}

void access(Node *x) {
    splay(x);
    x->r = nullptr;
    x->update();
    for (; x->p; splay(x)) {
        splay(x->p);
        x->p->r = x;
    }
}

void link(Node *p, Node *c) {
    access(p);
    access(c);
    c->l = p;
    p->p = c;
    c->update();
}

void cut(Node *x) {
    access(x);
    x->l->p = nullptr;
    x->l = nullptr;
    x->update();
}

Node *get_par(Node *x) {
    access(x);
    if (!x->l)
        return nullptr;
    x = x->l;
    x->push();
    while (x->r) {
        x = x->r;
        x->push();
    }
    splay(x);
    return x;
}

Node *get_lca(Node *x, Node *y) {
    access(x);
    access(y);
    splay(x);
    return x->p ? x->p : x;
}

void make_root(Node *x) {
    access(x);
    splay(x);
    x->flip ^= 1;
}

pair<int, int> query(Node *x, Node *y) {
    Node *lca = get_lca(x, y);
    pair<int, int> ret = lca->v;
    access(x);
    splay(lca);
    if (lca->r)
        ret = max(ret, lca->r->mx);
    access(y);
    splay(lca);
    if (lca->r)
        ret = max(ret, lca->r->mx);
    return ret;
}

int n, m;
long long sum, ans;
// [0, n): node, [n, n]: empty, [n + 1, 2n): edge
vector<Node> node;
// [0, n]: empty, (n, 2n): edge
vector<pair<int, int>> e;

inline void cut(Node *x, Node *y) { get_par(x) == y ? cut(x) : cut(y); }

int query(int x, int y, int c) {
    if (x == y)
        return 0;
    pair<int, int> tmp = query(&node[x], &node[y]);
    if (tmp.second == NODE or tmp.first <= c)
        return 0;

    cut(&node[tmp.second], &node[e[tmp.second].first]);
    cut(&node[tmp.second], &node[e[tmp.second].second]);
    node[tmp.second] = Node(c, tmp.second);
    make_root(&node[y]);
    link(&node[tmp.second], &node[y]);
    link(&node[x], &node[tmp.second]);
    e[tmp.second] = {x, y};

    return tmp.first - c;
}

void init() {
    int u, c;
    sum = ans = 0;
    node.clear();
    e.clear();

    cin >> n >> m;
    node.resize(n << 1);
    e.resize(n << 1);
    for (int i = 1; i < n; i++) {
        cin >> u >> c;

        node[i + n] = Node(c, i + n);
        e[i + n] = {i, u};
        sum += c;

        make_root(&node[i]);
        link(&node[i + n], &node[i]);
        link(&node[u], &node[i + n]);
    }
}

void solve() {
    int u, v, c;
    while (m--) {
        cin >> u >> v >> c;
        sum -= query(u, v, c);
        ans ^= sum;
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    while (tc--) {
        init();
        solve();
    }

    return 0;
}