#include <fstream>
#include <iostream>

using namespace std;

int n, q;
long long arr[101010];

struct Lazy {
    long long a, b, c;
    Lazy() : a(0), b(0), c(0) {}
    Lazy(long long c) : a(0), b(0), c(c) {}
};

struct Node {
    long long sz, d, sum;
    Lazy lz;
    Node *l, *r, *p;

    Node() : sz(1), d(0), sum(0), lz(), l(nullptr), r(nullptr), p(nullptr) {}
    Node(long long d, Node *p) : sz(1), d(d), sum(d), lz(), l(nullptr), r(nullptr), p(p) {}
};

struct splay_tree {
    Node *root;
    Node *ptr[101010];

    void push(Node *x) {
        if (x->lz.c) {
            if (x->l) {
                x->l->d = x->lz.c;
                x->l->sum = x->lz.c * x->l->sz;
                x->l->lz = Lazy(x->lz.c);
            }
            if (x->r) {
                x->r->d = x->lz.c;
                x->r->sum = x->lz.c * x->r->sz;
                x->r->lz = Lazy(x->lz.c);
            }
        }
        if (x->lz.a or x->lz.b) {
            if (x->l) {
                x->l->d += x->lz.a + x->lz.b * (x->l->l ? x->l->l->sz : 0);
                x->l->sum += x->lz.a * x->l->sz + x->lz.b * x->l->sz * (x->l->sz - 1) / 2;
                x->l->lz.a += x->lz.a;
                x->l->lz.b += x->lz.b;
            }
            if (x->r) {
                x->r->d += x->lz.a + x->lz.b * ((x->l ? x->l->sz + 1 : 1) + (x->r->l ? x->r->l->sz : 0));
                x->r->sum += (x->lz.a + x->lz.b * (x->l ? x->l->sz + 1 : 1)) * x->r->sz + x->lz.b * x->r->sz * (x->r->sz - 1) / 2;
                x->r->lz.a += x->lz.a + x->lz.b * (x->l ? x->l->sz + 1 : 1);
                x->r->lz.b += x->lz.b;
            }
        }
        x->lz = Lazy();
    }

    void update(Node *x) {
        x->sz = 1;
        x->sum = x->d;
        push(x);
        if (x->l) {
            x->sz += x->l->sz;
            x->sum += x->l->sum;
        }
        if (x->r) {
            x->sz += x->r->sz;
            x->sum += x->r->sum;
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

    void range_query(int s, int e, long long k) {
        auto x = gather(s, e);
        x->d += k * (x->l ? x->l->sz + 1 : 1);
        x->sum += k * ((e - s + 1) * (e - s + 2) / 2);
        x->lz.a += k;
        x->lz.b += k;
        splay(x);
    }

    void insert(int k, long long d) {
        kth(k);
        auto x = root->l;
        push(root);
        push(x);
        while (x->r) {
            x = x->r;
            push(x);
        }
        x->r = new Node(d, x);
        splay(x->r);
    }

    void init() {
        Node *x = root = new Node();
        for (int i = 0; i < n; i++) {
            ptr[i] = x->r = new Node(arr[i], x);
            x = x->r;
        }
        x->r = new Node(0, x);
        for (int i = n - 1; i >= 0; i--)
            update(ptr[i]);
        splay(ptr[n / 2]);
    }
} tree;

void init() {
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    tree.init();
}

void solve() {
    int op;
    long long a, b, x;

    while (q--) {
        cin >> op;
        if (op == 1) {
            cin >> a >> b >> x;
            auto v = tree.gather(a, b);
            v->sum += v->sz * x;
            v->d = x;
            v->lz = Lazy(x);
            tree.splay(v);
        }
        if (op == 2) {
            cin >> a >> b >> x;
            tree.range_query(a, b, x);
        }
        if (op == 3) {
            cin >> a >> x;
            tree.insert(a, x);
        }
        if (op == 4) {
            cin >> a >> b;
            cout << tree.gather(a, b)->sum << '\n';
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