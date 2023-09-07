#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, dst[101010];

struct Pair {
    int a, b;

    Pair(int a, int b) : a(a), b(b) {}

    bool operator<(const Pair &t) const { return (a == t.a ? b < t.b : a < t.a); }
};

struct Node {
    int sz;
    bool flip;
    Node *l, *r, *p;
    Node() : sz(1), flip(false), l(nullptr), r(nullptr), p(nullptr) {}
    Node(Node *p) : sz(1), flip(false), l(nullptr), r(nullptr), p(p) {}
};

struct splay_tree {
    Node *root;
    Node *ptr[101010];

    void push(Node *x) {
        if (!x->flip)
            return;
        swap(x->l, x->r);
        if (x->l)
            x->l->flip ^= 1;
        if (x->r)
            x->r->flip ^= 1;
        x->flip = false;
    }

    void update(Node *x) {
        x->sz = 1;
        if (x->l)
            x->sz += x->l->sz;
        if (x->r)
            x->sz += x->r->sz;
    }

    void rotate(Node *x) {
        Node *p = x->p;
        Node *b;
        push(p);
        push(x);
        if (p->l == x) {
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
        while (true) {
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
        auto tmp = gather(s, e);
        tmp->flip = !tmp->flip;
        splay(tmp);
    }

    void init() {
        Node *x = root = new Node();
        for (int i = 0; i < n; i++) {
            ptr[i] = x->r = new Node(x);
            x = x->r;
        }
        x->r = new Node(x);
        for (int i = n - 1; i >= 0; i--)
            update(ptr[i]);
        splay(ptr[n / 2]);
    }
} tree;

bool init() {
    cin >> n;
    if (n == 0)
        return false;

    vector<Pair> v;
    for (int i = 0; i < n; i++) {
        v.push_back(Pair(0, i));
        cin >> v[i].a;
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < n; i++)
        dst[i] = v[i].b;

    tree.init();

    return true;
}

void solve() {
    for (int i = 0; i < n; i++) {
        tree.splay(tree.ptr[dst[i]]);
        int kth = tree.root->l->sz;
        cout << kth << ' ';
        if (kth == i + 1)
            continue;
        tree.flip(i + 1, kth);
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (init())
        solve();

    return 0;
}