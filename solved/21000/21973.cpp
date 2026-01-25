#include <iostream>
#include <string>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#define N 30001

using namespace std;

int n, q;
int p[N];

struct Node {
    Node *l, *r, *p;
    int sz, v, sum;
    bool flip;

    bool is_root() { return !p or (this != p->l and this != p->r); }

    void update() {
        sz = 1;
        sum = v;
        if (l) {
            sz += l->sz;
            sum += l->sum;
        }
        if (r) {
            sz += r->sz;
            sum += r->sum;
        }
    }

    void update(int x) {
        v = x;
        update();
    }

    void rotate() {
        Node *b;
        if (this == p->l) {
            p->l = b = r;
            r = p;
        } else {
            p->r = b = l;
            l = p;
        }
        if (b)
            b->p = p;
        if (!p->is_root())
            (p->p->l == p ? p->p->l : p->p->r) = this;
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
            l->flip = !l->flip;
        if (r)
            r->flip = !r->flip;
        flip = false;
    }

    Node() : sz(1), v(0), sum(0) {}
} node[N];

void splay(Node *x) {
    for (; !x->is_root(); x->rotate()) {
        if (!x->p->is_root())
            x->p->p->push();
        x->p->push();
        x->push();
        if (x->p->is_root())
            continue;
        auto pp = x->p;
        if ((x->p == x) == (pp->l == x->p))
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
    x->flip = !x->flip;
}

void link(Node *p, Node *c) {
    make_root(c);
    access(c);
    access(p);
    c->l = p;
    p->p = c;
}

Node *get_lca(Node *x, Node *y) {
    access(x);
    access(y);
    splay(x);
    return x->p ? x->p : x;
}

int query(Node *x, Node *y) {
    Node *l = get_lca(x, y);
    int ret = l->v;
    access(x);
    splay(l);
    if (l->r)
        ret = ret + l->r->sum;
    access(y);
    splay(l);
    if (l->r)
        ret = ret + l->r->sum;
    return ret;
}

int find_root(int x) {
    if (x == p[x])
        return x;
    return p[x] = find_root(p[x]);
}

bool union_root(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b)
        return false;
    p[a] = b;
    return true;
}

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        p[i] = i;

    int x;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        node[i].update(x);
    }
    cin >> q;
}

void solve() {
    string op;
    int a, b;
    while (q--) {
        cin >> op >> a >> b;
        if (op[0] == 'b') {
            if (union_root(a, b)) {
                link(&node[a], &node[b]);
                cout << "yes" << endl;
            } else
                cout << "no" << endl;
        }
        if (op[0] == 'e') {
            if (find_root(a) != find_root(b))
                cout << "impossible" << endl;
            else
                cout << query(&node[a], &node[b]) << endl;
        }
        if (op[0] == 'p') {
            splay(&node[a]);
            node[a].update(b);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    init();
    solve();

    return 0;
}