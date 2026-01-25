#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#define N 200000
#define MASK 1048575

using namespace std;

struct Node {
    int mx, v_and, v_or, lz_and, lz_or;

    Node operator+(const Node &t) const { return Node(max(mx, t.mx), v_and & t.v_and, v_or | t.v_or); }

    Node(int mx = 0, int v_and = 0, int v_or = 0) : mx(mx), v_and(v_and), v_or(v_or), lz_and(0), lz_or(0) {}
} tree[N << 2];

int n, m;

inline int mask(int x) { return MASK ^ x; }

void push(int i) {
    for (auto a : {i << 1, i << 1 | 1}) {
        tree[a].mx &= mask(tree[i].lz_and);
        tree[a].v_and &= mask(tree[i].lz_and);
        tree[a].v_or &= mask(tree[i].lz_and);
        tree[a].lz_and |= tree[i].lz_and;
        tree[a].lz_or &= mask(tree[i].lz_and);

        tree[a].mx |= tree[i].lz_or;
        tree[a].v_and |= tree[i].lz_or;
        tree[a].v_or |= tree[i].lz_or;
        tree[a].lz_or |= tree[i].lz_or;
    }
    tree[i].lz_and = 0;
    tree[i].lz_or = 0;
}

void tree_init(int s, int e, int i = 1) {
    if (s == e) {
        cin >> tree[i].mx;
        tree[i].v_and = tree[i].v_or = tree[i].mx;
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void update_and(int l, int r, int x, int s, int e, int i = 1) {
    if (e < l or r < s or (x & tree[i].v_or) == 0)
        return;
    x -= x & mask(tree[i].v_or);
    if (l <= s and e <= r and x & tree[i].v_and) {
        int tmp = x & tree[i].v_and;
        tree[i].mx &= mask(tmp);
        tree[i].v_and &= mask(tmp);
        tree[i].v_or &= mask(tmp);
        tree[i].lz_and |= tmp;
        tree[i].lz_or &= mask(tmp);
        x -= tmp;
    }
    if (!x)
        return;
    push(i);
    update_and(l, r, x, s, (s + e) / 2, i << 1);
    update_and(l, r, x, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void update_or(int l, int r, int x, int s, int e, int i = 1) {
    if (e < l or r < s or (x & tree[i].v_and) == x)
        return;
    x -= x & tree[i].v_and;
    if (l <= s and e <= r and x & mask(tree[i].v_or)) {
        int tmp = x & mask(tree[i].v_or);
        tree[i].mx |= tmp;
        tree[i].v_and |= tmp;
        tree[i].v_or |= tmp;
        tree[i].lz_or |= tmp;
        x -= tmp;
    }
    if (!x)
        return;
    push(i);
    update_or(l, r, x, s, (s + e) / 2, i << 1);
    update_or(l, r, x, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

int query(int l, int r, int s, int e, int i = 1) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i].mx;
    push(i);
    return max(query(l, r, s, (s + e) / 2, i << 1), query(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
}

void init() {
    cin >> n;
    tree_init(1, n);
    cin >> m;
}

void solve() {
    int op, l, r, x;
    while (m--) {
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> x;
            update_and(l, r, mask(x), 1, n);
        }
        if (op == 2) {
            cin >> x;
            update_or(l, r, x, 1, n);
        }
        if (op == 3)
            cout << query(l, r, 1, n) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();

    return 0;
}