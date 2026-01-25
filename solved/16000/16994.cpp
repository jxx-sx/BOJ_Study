#include <iostream>
#include <string>

using namespace std;

string st;
int q;

struct Node {
    char d;
    int sz;
    Node *l, *r, *p;
    bool flip, dummy;
    Node() : d(0), sz(1), l(nullptr), r(nullptr), p(nullptr), flip(false), dummy(false) {}
    Node(char d, Node *p) : d(d), sz(1), l(nullptr), r(nullptr), p(p), flip(false), dummy(false) {}
};

struct splay_tree {
    Node *root;

    void push(Node *x) {
        if (!x->flip)
            return;
        swap(x->l, x->r);
        if (x->l)
            x->l->flip = !x->l->flip;
        if (x->r)
            x->r->flip = !x->r->flip;
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
            if ((p->l == x) == (pp->l == p)) {
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
            while (x->l && x->l->sz > k) {
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

    void shift(int s, int e, int op) {
        if (op) {
            if (e == st.size())
                return;
            flip(s, st.size());
            flip(st.size() - e + s, st.size());
            flip(s, st.size() - e + s - 1);
        } else {
            if (s == 1)
                return;
            flip(1, e);
            flip(1, e - s + 1);
            flip(e - s + 2, e);
        }
    }

    void init() {
        Node *x = root = new Node();
        for (auto a : st) {
            x->r = new Node(a, x);
            x = x->r;
        }
        x->r = new Node(0, x);
        x->r->dummy = root->dummy = true;
        for (int i = 0; i < st.size(); i++) {
            update(x);
            x = x->p;
        }
        splay(root->r);
    }

} tree;

void init() {
    cin >> st >> q;
    tree.init();
}

void solve() {
    int op, x, y;
    while (q--) {
        cin >> op >> x;
        if (op == 3) {
            tree.kth(x + 1);
            cout << tree.root->d << '\n';
            continue;
        }
        cin >> y;
        tree.shift(x + 1, y + 1, op - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}