#include <iostream>
#include <string>

using namespace std;

struct Node {
    char d;
    int sz;
    Node *p, *l, *r;

    Node(char d, Node *p) : d(d), sz(1), p(p), l(nullptr), r(nullptr) {}
};

struct splay_tree {
    Node *root;

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

        update(x);
        update(p);
    }

    void splay(Node *x, Node *g = nullptr) {
        while (x->p != g) {
            Node *p = x->p;
            if (p->p == g) {
                rotate(x);
                break;
            }
            auto pp = p->p;
            if ((pp->l == p) == (p->l == x)) {
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
        Node *cur = root;
        while (true) {
            while (cur->l and cur->l->sz > k)
                cur = cur->l;
            if (cur->l)
                k -= cur->l->sz;
            if (!k--)
                break;
            cur = cur->r;
        }
        splay(cur);
    }

    Node *gather(int s, int e) {
        kth(e + 1);
        auto tmp = root;
        kth(s - 1);
        splay(tmp, root);
        return root->r->l;
    }

    void insert() {
        string st;
        int k;
        cin >> st >> k;
        kth(k + 1);
        Node *cur = root->l;
        while (cur->r)
            cur = cur->r;
        Node *tmp = cur;
        for (auto a : st) {
            cur->r = new Node(a, cur);
            cur = cur->r;
        }
        while (cur != tmp->p) {
            update(cur);
            cur = cur->p;
        }
        splay(cur);
    }

    void init() {
        string st;
        cin >> st;
        Node *cur = root = new Node(0, nullptr);
        for (auto a : st) {
            cur->r = new Node(a, cur);
            cur = cur->r;
        }
        cur->r = new Node(0, cur);
        while (cur != root) {
            update(cur);
            cur = cur->p;
        }

        splay(root->r);
    }
} tree;

void dfs(Node *x) {
    if (x->l)
        dfs(x->l);
    if (x->d != 0)
        cout << x->d;
    if (x->r)
        dfs(x->r);
}

void init() { tree.init(); }

void solve() {
    string op;
    int l, r;
    while (true) {
        cin >> op;
        if (op == "I")
            tree.insert();
        else if (op == "P") {
            cin >> l >> r;
            dfs(tree.gather(l + 1, r + 1));
            cout << '\n';
        } else
            break;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        init();
        solve();
    }

    return 0;
}