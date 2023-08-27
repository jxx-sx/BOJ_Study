#include <iostream>

using namespace std;

int n, q;
struct Node {
    Node *l;
    Node *r;
    Node *p;
    int cnt, d, mx, mn;
    long long sum;
    bool flip, dummy;
    Node() : l(nullptr), r(nullptr), p(nullptr), cnt(1), d(0), mx(0), mn(0), sum(0), flip(false), dummy(false) {}
    Node(int d) : l(nullptr), r(nullptr), p(nullptr), cnt(1), d(d), mx(d), mn(d), sum(d), flip(false), dummy(false) {}
    Node(int d, Node *p) : l(nullptr), r(nullptr), p(p), cnt(1), d(d), mx(d), mn(d), sum(d), flip(false), dummy(false) {}
};
Node *tree, *node[300001];

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
    x->cnt = 1;
    x->sum = x->mx = x->mn = x->d;
    if (x->l) {
        x->cnt += x->l->cnt;
        x->mx = max(x->mx, x->l->mx);
        x->mn = min(x->mn, x->l->mn);
        x->sum += x->l->sum;
    }
    if (x->r) {
        x->cnt += x->r->cnt;
        x->mx = max(x->mx, x->r->mx);
        x->mn = min(x->mn, x->r->mn);
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
    (x->p ? p == x->p->l ? x->p->l : x->p->r : tree) = x;
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
        tree = x;
}

void kth(int k) {
    Node *x = tree;
    push(x);
    while (1) {
        while (x->l && x->l->cnt > k) {
            x = x->l;
            push(x);
        }
        if (x->l)
            k -= x->l->cnt;
        if (!k--)
            break;
        x = x->r;
        push(x);
    }
    splay(x);
}

Node *gather(int s, int e) {
    kth(e + 1);
    auto tmp = tree;
    kth(s - 1);
    splay(tmp, tree);
    return tree->r->l;
}

void flip(int s, int e) {
    Node *x = gather(s, e);
    x->flip = !x->flip;
}

void shift(int s, int e, int k) {
    if (k > 0) {
        k %= (e - s + 1);
        if (k) {
            flip(s, e);
            flip(s, s + k - 1);
            flip(s + k, e);
        }
    } else {
        k *= -1;
        k %= (e - s + 1);
        if (k) {
            flip(s, e);
            flip(s, e - k);
            flip(e - k + 1, e);
        }
    }
}

void tree_init() {
    Node *cur;
    cur = tree = new Node(0);
    for (int i = 1; i <= n; i++) {
        node[i] = cur->r = new Node(i, cur);
        cur = cur->r;
    }
    cur->r = new Node(n + 1, cur);
    cur->r->dummy = tree->dummy = true;
    for (int i = n; i >= 1; i--)
        update(node[i]);
    splay(node[n / 2]);
}

void dfs(Node *cur) {
    push(cur);
    if (cur->l)
        dfs(cur->l);
    if (!cur->dummy)
        cout << cur->d << ' ';
    if (cur->r)
        dfs(cur->r);
}

void init() {
    cin >> n >> q;
    tree_init();
}

void solve() {
    int op, l, r, k;
    while (q--) {
        cin >> op;
        if (op == 1) {
            cin >> l >> r;
            Node *x = gather(l, r);
            cout << x->mn << " " << x->mx << " " << x->sum << "\n";
            x->flip = !x->flip;
        }
        if (op == 2) {
            cin >> l >> r >> k;
            Node *x = gather(l, r);
            cout << x->mn << " " << x->mx << " " << x->sum << "\n";
            shift(l, r, k);
        }
        if (op == 3) {
            cin >> k;
            kth(k);
            cout << tree->d << '\n';
        }
        if (op == 4) {
            cin >> k;
            splay(node[k]);
            cout << tree->l->cnt << '\n';
        }
    }
    dfs(tree);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}