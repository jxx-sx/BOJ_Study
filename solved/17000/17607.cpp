#include <algorithm>
#include <iostream>

using namespace std;

int n, m, arr[101010];

struct Node {
    int sz, d, lm, rm, mx;
    Node *l, *r, *p;
    bool flip;
    Node() : sz(1), d(0), lm(0), rm(0), mx(0), l(nullptr), r(nullptr), p(nullptr), flip(false) {}
    Node(int d, Node *p) : sz(1), d(d), lm(d), rm(d), mx(d), l(nullptr), r(nullptr), p(p), flip(false) {}
};

struct splay_tree {
    Node *root;
    Node *ptr[101010];

    void push(Node *x) {
        if (!x->flip)
            return;
        swap(x->l, x->r);
        swap(x->lm, x->rm);
        if (x->l)
            x->l->flip = !x->l->flip;
        if (x->r)
            x->r->flip = !x->r->flip;
        x->flip = false;
    }

    void update(Node *x) {
        push(x);
        x->sz = 1;
        x->lm = x->rm = x->mx = x->d;
        if (x->l and x->r) {
            push(x->l);
            push(x->r);
            x->lm = (x->d && x->l->lm == x->l->sz) ? x->l->lm + x->r->lm + 1 : x->l->lm;
            x->rm = (x->d && x->r->rm == x->r->sz) ? x->l->rm + x->r->rm + 1 : x->r->rm;
            x->mx = x->d ? max({x->l->rm + x->r->lm + 1, x->lm, x->rm, x->l->mx, x->r->mx}) : max(x->l->mx, x->r->mx);
            x->sz += x->l->sz + x->r->sz;
        } else if (x->l) {
            push(x->l);
            x->lm = (x->d && x->l->lm == x->l->sz) ? x->l->lm + 1 : x->l->lm;
            x->rm = x->d ? x->l->rm + 1 : 0;
            x->mx = x->d ? max(x->l->mx, x->rm) : x->l->mx;
            x->sz += x->l->sz;
        } else if (x->r) {
            push(x->r);
            x->lm = x->d ? x->r->lm + 1 : 0;
            x->rm = (x->d && x->r->rm == x->r->sz) ? x->r->rm + 1 : x->r->rm;
            x->mx = x->d ? max(x->lm, x->r->mx) : x->r->mx;
            x->sz += x->r->sz;
        }
    }

    void rotate(Node *x) {
        Node *p = x->p;
        Node *b;
        push(p);
        push(x);
        if (x == p->l) {
            p->l = b = x->r;
            x->r = p;
        } else {
            p->r = b = x->l;
            x->l = p;
        }
        x->p = p->p;
        p->p = x;
        if (b)
            b->p = p;
        (x->p ? x->p->l == p ? x->p->l : x->p->r : root) = x;
        update(p);
        update(x);
    }

    void splay(Node *x, Node *g = nullptr) {
        while (x->p != g) {
            Node *p = x->p;
            if (p->p == g) {
                rotate(x);
                break;
            }
            auto pp = p->p;
            if ((x == p->l) == (p == pp->l)) {
                rotate(p);
                rotate(x);
            } else {
                rotate(x);
                rotate(x);
            }
        }
        if (!g)
            root = x;
    }

    void kth(int k) {
        Node *x = root;
        push(x);
        while (1) {
            while (x->l and x->l->sz > k) {
                x = x->l;
                push(x);
            }
            if (x->l)
                k -= x->l->sz;
            if (!k--)
                break;
            x = x->r;
            push(x);
        }
        splay(x);
    }

    Node *gather(int s, int e) {
        kth(e + 1);
        auto tmp = root;
        kth(s - 1);
        splay(tmp, root);
        return root->r->l;
    }

    void flip(int s, int e) {
        Node *x = gather(s, e);
        x->flip = !x->flip;
    }

    void init() {
        Node *x = root = new Node();
        for (int i = 0; i < n; i++) {
            ptr[i] = x->r = new Node(arr[i], x);
            x = x->r;
        }
        x->r = new Node(0, x);
        for (int i = n - 1; i >= 0; i--) {
            update(ptr[i]);
        }
        rotate(ptr[n / 2]);
    }
} tree;

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    tree.init();
    cin >> m;
}

void solve() {
    int op, l, r;
    while (m--) {
        cin >> op >> l >> r;
        if (op == 1)
            tree.flip(l, r);
        else
            cout << tree.gather(l, r)->mx << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}