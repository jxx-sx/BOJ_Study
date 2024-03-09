#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>

#define INF 1010101010

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Node {
    Node *p, *l, *r;
    pair<int, int> v, mn;
    bool flip;

    bool is_root() { return !p or (this != p->l and this != p->r); }
    bool is_left() { return this == p->l; }

    void push() {
        if (!flip)
            return;
        swap(l, r);
        if (l)
            l->flip ^= 1;
        if (r)
            r->flip ^= 1;
        flip = 0;
    }

    void update() { mn = min({v, l ? l->mn : v, r ? r->mn : v}); }

    void update(int d) {
        v.first = d;
        update();
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
} node[720000];
pair<int, int> edges[720000];
set<pair<int, int>> s;
int n, q, cnt;

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

void cut(Node *x) {
    access(x);
    x->l->p = nullptr;
    x->l = nullptr;
    x->update();
}

void cut(Node *x, Node *y) { get_par(x) == y ? cut(x) : cut(y); }

Node *get_root(Node *x) {
    access(x);
    while (x->l) {
        x = x->l;
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

pair<int, int> get_mn(Node *x, Node *y) {
    Node *lca = get_lca(x, y);
    pair<int, int> ret = lca->v;
    access(x);
    splay(lca);
    if (lca->r)
        ret = min(ret, lca->r->mn);
    access(y);
    splay(lca);
    if (lca->r)
        ret = min(ret, lca->r->mn);
    return ret;
}

void init() {
    cin >> n >> q;
    cnt = n;
    for (int i = 1; i < 720000; i++)
        node[i].mn = node[i].v = {INF, i};
}

void solve() {
    int op, i, j, d, x;
    while (q--) {
        cin >> op;
        if (op == 1) {
            cin >> i >> j >> d;
            if (get_root(node + i) == get_root(node + j)) {
                auto [mn, idx] = get_mn(node + i, node + j);
                if (mn >= d)
                    continue;
                auto [a, b] = edges[idx];
                cut(node + idx, node + a);
                cut(node + idx, node + b);
                s.erase({mn, idx});
            }
            ++cnt;
            node[cnt].update(d);
            edges[cnt] = {i, j};
            make_root(node + j);
            link(node + cnt, node + j);
            link(node + i, node + cnt);
            s.insert({d, cnt});
        }
        if (op == 2) {
            cin >> x;
            while (!s.empty()) {
                auto [mn, idx] = *s.begin();
                if (mn >= x)
                    break;
                auto [a, b] = edges[idx];
                cut(node + idx, node + a);
                cut(node + idx, node + b);
                s.erase(s.begin());
            }
        }
        if (op == 3) {
            cin >> i >> j;
            cout << (get_root(node + i) == get_root(node + j) ? get_mn(node + i, node + j).first : 0) << '\n';
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