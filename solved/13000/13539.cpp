#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Node {
    int sz;
    Node *l, *r, *p;

    bool isRoot() { return !p or (this != p->l and this != p->r); }

    bool isLeft() { return this == p->l; }

    void rotate() {
        Node *b;
        if (p->l == this) {
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
        if (!p->isRoot()) {
            Node *pp = p->p;
            (p == pp->l ? pp->l : pp->r) = this;
        }
        Node *tmp = p;
        p = tmp->p;
        tmp->p = this;
        tmp->update();
        update();
    }

    void update() {
        sz = 1;
        if (l)
            sz += l->sz;
        if (r)
            sz += r->sz;
    }
};

void splay(Node *x) {
    while (!x->isRoot()) {
        if (x->p->isRoot()) {
            x->rotate();
            break;
        }
        auto p = x->p;
        auto pp = p->p;
        if ((x == p->l) == (p == pp->l))
            p->rotate();
        else
            x->rotate();
        x->rotate();
    }
}

void access(Node *x) {
    splay(x);
    x->r = nullptr;
    while (x->p) {
        splay(x->p);
        x->p->r = x;
        splay(x);
    }
}

void link(Node *p, Node *c) {
    access(p);
    access(c);
    c->l = p;
    p->p = c;
}

void cut(Node *x) {
    access(x);
    x->l->p = nullptr;
    x->l = nullptr;
}

Node *lca(Node *a, Node *b) {
    access(a);
    access(b);
    splay(a);
    return a->p ? a->p : a;
}

Node node[100001];
int n, m;

void init() { cin >> n >> m; }

void solve() {
    int op, u, v;
    while (m--) {
        cin >> op;
        if (op == 1) {
            cin >> u >> v;
            link(&node[v], &node[u]);
        }
        if (op == 2) {
            cin >> v;
            cut(&node[v]);
        }
        if (op == 3) {
            cin >> u >> v;
            cout << lca(&node[v], &node[u]) - node << '\n';
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