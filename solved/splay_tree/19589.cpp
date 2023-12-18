#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, q, ind;

struct Node {
    int d, sz;
    bool flip;
    Node *l, *r, *p;

    Node(int d, Node *p) : d(d), sz(1), flip(false), l(nullptr), r(nullptr), p(p) {}
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
        Node *b;
        Node *p = x->p;

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
        (x->p ? p == x->p->l ? x->p->l : x->p->r : root) = x;
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
        push(x);
        while (true) {
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
        auto tmp = gather(s, e);
        tmp->flip = !tmp->flip;
        splay(tmp);
    }

    void query1(int x, int y) {
        if (x == 1)
            return;
        flip(x, y);
        flip(1, x - 1);
        flip(1, y);
    }
    void query2(int x, int y) {
        if (y == n)
            return;
        flip(x, y);
        flip(y + 1, n);
        flip(x, n);
    }
    void query3(int x, int y) {
        ind = 0;
        vector<int> v;
        vector<int> shuffle(y - x + 1);
        dfs(gather(x, y), v);
        shuffle[0] = v[0];

        for (int i = 1, j = 2; i < ((y - x + 2) >> 1); i++, j += 2)
            shuffle[j] = v[i];
        for (int i = ((y - x + 2) >> 1), j = 1; i < v.size(); i++, j += 2)
            shuffle[j] = v[i];
        set(root->r->l, &shuffle);
    }

    void print() { dfs(root); }

    void dfs(Node *x) {
        push(x);
        if (x->l)
            dfs(x->l);
        if (x->d)
            cout << x->d << ' ';
        if (x->r)
            dfs(x->r);
    }

    void dfs(Node *x, vector<int> &v) {
        push(x);
        if (x->l)
            dfs(x->l, v);
        v.push_back(x->d);
        if (x->r)
            dfs(x->r, v);
    }

    void set(Node *x, vector<int> *v) {
        push(x);
        if (x->l)
            set(x->l, v);
        x->d = (*v)[ind];
        ind++;
        if (x->r)
            set(x->r, v);
    }

    void init() {
        Node *cur = root = new Node(0, nullptr);
        for (int i = 1; i <= n; i++) {
            cur->r = new Node(i, cur);
            cur = cur->r;
        }
        cur->r = new Node(0, cur);

        while (cur) {
            update(cur);
            cur = cur->p;
        }
        splay(root->r);
    }
} tree;

void init() {
    cin >> n >> q;
    tree.init();
}

void solve() {
    int op, x, y;
    while (q--) {
        cin >> op >> x >> y;
        if (op == 1)
            tree.query1(x, y);
        if (op == 2)
            tree.query2(x, y);
        if (op == 3)
            tree.query3(x, y);
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