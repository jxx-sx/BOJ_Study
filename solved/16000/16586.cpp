#include <cassert>
#include <iostream>
#include <string>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, q;

struct Node {
    int sz, d;
    Node *l, *r, *p;

    Node(int d, Node *p) : sz(1), d(d), l(nullptr), r(nullptr), p(p) {}
};

struct splay_tree {
    Node *root;
    Node *arr[100001];

    void update(Node *x) {
        x->sz = 1;
        if (x->l)
            x->sz += x->l->sz;
        if (x->r)
            x->sz += x->r->sz;
    }

    void rotate(Node *x) {
        Node *b;
        Node *p = x->p;
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
            Node *pp = p->p;
            if ((pp->l == p) == (p->l == x))
                rotate(p);
            else
                rotate(x);
            rotate(x);
        }
        if (!g)
            root = x;
    }

    void kth(int k) {
        Node *x = root;
        while (true) {
            while (x->l and x->l->sz > k)
                x = x->l;
            if (x->l)
                k -= x->l->sz;
            if (!k--)
                break;
            x = x->r;
        }
        splay(x);
    }

    void gather(int a, int b) {
        kth(b + 1);
        auto tmp = root;
        kth(a - 1);
        splay(tmp, root);
    }

    void query(int a, int b) {
        splay(arr[a]);
        int tmp_a = root->l->sz;
        splay(arr[b]);
        int tmp_b = root->l->sz;
        if (tmp_a > tmp_b)
            cout << tmp_b - tmp_a + 1 << '\n';
        else {
            cout << tmp_b - tmp_a << '\n';
            tmp_b--;
        }
        gather(tmp_a, tmp_a);
        root->r->l = nullptr;
        update(root->r);
        update(root);
        gather(tmp_b, tmp_b);
        root->r->l->r = arr[a];
        arr[a]->p = arr[b];
        splay(arr[a]);
    }

    void print() { dfs(root); }

    void dfs(Node *x) {
        if (x->l)
            dfs(x->l);
        if (x->d)
            cout << x->d << ' ';
        if (x->r)
            dfs(x->r);
    }

    void init() {
        Node *cur = root = new Node(0, nullptr);
        for (int i = 1; i <= n; i++) {
            arr[i] = cur->r = new Node(i, cur);
            cur = cur->r;
        }
        cur->r = new Node(0, cur);

        while (cur) {
            update(cur);
            cur = cur->p;
        }
        assert(arr[(n + 1) >> 1] != nullptr);
        splay(arr[(n + 1) >> 1]);
    }
} tree;

void init() {
    cin >> n >> q;
    tree.init();
}

void solve() {
    int a, b;
    while (q--) {
        cin >> a >> b;
        tree.query(a, b);
    }
    tree.print();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
