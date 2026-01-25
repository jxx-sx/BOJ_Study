#include <iostream>

using namespace std;

struct Node {
    int d, l, r;
    Node() : d(0), l(0), r(0) {}
} tree[12000000];

int m, ord, cur;

void tree_init(int i, int d) {
    if (d < 0)
        return;
    tree[i].l = ord++;
    tree[i].r = ord++;
    tree_init(tree[i].l, d - 1);
    tree_init(tree[i].r, d - 1);
}

void tree_init1(int k, int i, int b, int d) {
    tree[i].d = tree[b].d + 1;
    if (d < 0)
        return;
    if (k & (1 << d)) {
        tree[i].l = tree[b].l;
        tree[i].r = ord++;
        tree_init1(k, tree[i].r, tree[b].r, d - 1);
    } else {
        tree[i].l = ord++;
        tree[i].r = tree[b].r;
        tree_init1(k, tree[i].l, tree[b].l, d - 1);
    }
}

int xor_query(int x, int l, int r, int d) {
    if (d < 0)
        return 0;
    if (x & (1 << d))
        if (tree[tree[r].l].d - tree[tree[l].l].d)
            return xor_query(x, tree[l].l, tree[r].l, d - 1);
    if (tree[tree[r].r].d - tree[tree[l].r].d == 0)
        return xor_query(x, tree[l].l, tree[r].l, d - 1);
    return xor_query(x, tree[l].r, tree[r].r, d - 1) | (1 << d);
}

int cnt_query(int x, int l, int r, int d) {
    if (d < 0)
        return tree[r].d - tree[l].d;
    if (x & (1 << d)) {
        return tree[tree[r].l].d - tree[tree[l].l].d + cnt_query(x, tree[l].r, tree[r].r, d - 1);
    }
    return cnt_query(x, tree[l].l, tree[r].l, d - 1);
}

int get_query(int x, int l, int r, int d) {
    if (d < 0)
        return 0;
    int ll = tree[tree[r].l].d - tree[tree[l].l].d;
    if (x > ll)
        return get_query(x - ll, tree[l].r, tree[r].r, d - 1) | (1 << d);
    return get_query(x, tree[l].l, tree[r].l, d - 1);
}

void init() {
    cin >> m;
    ord = 500001;
    tree_init(0, 18);
}

void solve() {
    int op, x, l, r;
    while (m--) {
        cin >> op;
        if (op == 1) {
            cin >> x;
            tree_init1(x, cur + 1, cur, 18);
            cur++;
        }
        if (op == 2) {
            cin >> l >> r >> x;
            cout << xor_query(x, l - 1, r, 18) << '\n';
        }
        if (op == 3) {
            cin >> x;
            cur -= x;
        }
        if (op == 4) {
            cin >> l >> r >> x;
            cout << cnt_query(x, l - 1, r, 18) << '\n';
        }
        if (op == 5) {
            cin >> l >> r >> x;
            cout << get_query(x, l - 1, r, 18) << '\n';
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