#include <iostream>
using namespace std;

int tree[2000000];
int lazy[2000000];
int n, m;

void propagate(int s, int e, int i) {
    if (lazy[i] == 0)
        return;
    if (s != e) {
        lazy[i << 1] ^= lazy[i];
        lazy[(i << 1) | 1] ^= lazy[i];
    }
    if (((e - s) & 1) == 0)
        tree[i] ^= lazy[i];
    lazy[i] = 0;
}

bool range(int l, int r, int s, int e) {
    if (e < l or r < s)
        return false;
    return (((min(e, r) - max(s, l)) & 1) == 0);
}

int tree_init(int s, int e, int i) {
    if (s == e) {
        cin >> tree[i];
        return tree[i];
    }
    return tree[i] = tree_init(s, (s + e) / 2, i << 1) ^ tree_init((s + e) / 2 + 1, e, (i << 1) | 1);
}

void update_range(int l, int r, int s, int e, int i, int k) {
    propagate(s, e, i);
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        if (s != e) {
            lazy[i << 1] ^= k;
            lazy[(i << 1) | 1] ^= k;
        }
        if (((e - s) & 1) == 0)
            tree[i] ^= k;
        return;
    }
    if (range(l, r, s, e))
        tree[i] ^= k;
    update_range(l, r, s, (s + e) / 2, i << 1, k);
    update_range(l, r, (s + e) / 2 + 1, e, (i << 1) | 1, k);
}

int tree_find(int l, int r, int s, int e, int i) {
    propagate(s, e, i);
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];
    return tree_find(l, r, s, (s + e) / 2, i << 1) ^ tree_find(l, r, (s + e) / 2 + 1, e, (i << 1) | 1);
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
            cin >> b >> c;
            cout << tree_find(b, c, 0, n - 1, 1) << '\n';
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