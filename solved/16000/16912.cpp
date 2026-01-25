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
} node[100001];

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

void make_root(Node *x) {
    access(x);
    splay(x);
    x->flip ^= 1;
}

void link(Node *p, Node *c) {
    make_root(c);
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

Node *get_root(Node *x) {
    access(x);
    while (x->l) {
        x = x->l;
        x->push();
    }
    splay(x);
    return x;
}

int n, m;

inline void cut(Node *x, Node *y) { get_par(x) == y ? cut(x) : cut(y); }

void init() { cin >> n >> m; }

void solve() {
    int op, a, b;
    while (m--) {
        cin >> op >> a >> b;
        if (op == 1)
            link(node + a, node + b);
        if (op == 2)
            cut(node + a, node + b);
        if (op == 3)
            cout << (get_root(node + a) == get_root(node + b) ? 1 : 0) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}