#include <iostream>

using namespace std;

int tree[2000000];
int ind[500001];
int n;

int tree_init(int s, int e, int i) {
    if (s == e) {
        ind[s] = i;
        cin >> tree[i];
        return tree[i];
    }
    return tree[i] = tree_init(s, (s + e) / 2, i << 1) + tree_init((s + e) / 2 + 1, e, i << 1 | 1);
}

void tree_update(int i, int d) {
    i = ind[i];
    while (i != 0) {
        tree[i] += d;
        i >>= 1;
    }
}

int tree_find(int order, int s, int e, int i) {
    if (s == e)
        return e;
    if (tree[i << 1] < order)
        return tree_find(order - tree[i << 1], (s + e) / 2 + 1, e, i << 1 | 1);
    else
        return tree_find(order, s, (s + e) / 2, i << 1);
}

void init() {
    cin >> n;
    tree_init(1, n, 1);

    return;
}

void solve() {
    int m, q, a, b;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q;
        if (q == 1) {
            cin >> a >> b;
            tree_update(a, b);
        } else {
            cin >> a;
            cout << tree_find(a, 1, n, 1) << '\n';
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