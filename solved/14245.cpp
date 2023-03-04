#include <iostream>
#define MAX_SIZE 500000
using namespace std;

int tree[MAX_SIZE << 2];
int lazy[MAX_SIZE << 2];
int n, m;

void propagate(int s, int e, int i) {
    if (lazy[i] == 0)
        return;
    if (s != e) {
        lazy[i << 1] ^= lazy[i];
        lazy[(i << 1) | 1] ^= lazy[i];
    } else
        tree[i] ^= lazy[i];
    lazy[i] = 0;
}

void tree_init(int s, int e, int i) {
    if (s == e) {
        cin >> tree[i];
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, (i << 1) | 1);
}

void update_range(int l, int r, int s, int e, int i, int d) {
    propagate(s, e, i);
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        if (s != e) {
            lazy[i << 1] ^= d;
            lazy[(i << 1) | 1] ^= d;
        } else
            tree[i] ^= d;
        return;
    }
    update_range(l, r, s, (s + e) / 2, i << 1, d);
    update_range(l, r, (s + e) / 2 + 1, e, (i << 1) | 1, d);
}
int tree_find(int x, int s, int e, int i) {
    propagate(s, e, i);
    if (e < x or x < s)
        return 0;
    if (s == x and e == x) {
        return tree[i];
    }
    return tree_find(x, s, (s + e) / 2, i << 1) ^ tree_find(x, (s + e) / 2 + 1, e, (i << 1) | 1);
}

void init() {
    cin >> n;
    tree_init(0, n - 1, 1);
    cin >> m;
    return;
}

void solve() {
    int a, b, c, d;
    for (int i = 0; i < m; i++) {
        cin >> a;
        if (a == 1) {
            cin >> b >> c >> d;
            update_range(b, c, 0, n - 1, 1, d);
        } else {
            cin >> b;
            cout << tree_find(b, 0, n - 1, 1) << '\n';
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