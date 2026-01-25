#include <iostream>
#define MAX_SIZE 100000

using namespace std;

int n;
long long tree[MAX_SIZE * 4];
long long lazy[MAX_SIZE * 4];

void propagate(int s, int e, int i) {
    if (lazy[i] == 0)
        return;
    if (s != e) {
        lazy[i << 1] += lazy[i];
        lazy[(i << 1) | 1] += lazy[i];
    } else
        tree[i] += lazy[i];
    lazy[i] = 0;
}

int range(int l, int r, int s, int e) {
    if (e < l or r < s)
        return 0;
    return min(e, r) - max(s, l) + 1;
}

void tree_init(int s, int e, int i) {
    if (s == e) {
        cin >> tree[i];
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, (i << 1) | 1);
}

void tree_update_range(int l, int r, int s, int e, int i, int k) {
    propagate(s, e, i);
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        if (s != e) {
            lazy[i << 1] += k;
            lazy[(i << 1) | 1] += k;
        } else
            tree[i] += k;
        return;
    }
    tree_update_range(l, r, s, (s + e) / 2, i << 1, k);
    tree_update_range(l, r, (s + e) / 2 + 1, e, (i << 1) | 1, k);
}

long long tree_find(int x, int s, int e, int i) {
    propagate(s, e, i);
    if (e < x or x < s)
        return 0;
    if (s == x and e == x)
        return tree[i];
    return tree_find(x, s, (s + e) / 2, i << 1) + tree_find(x, (s + e) / 2 + 1, e, (i << 1) | 1);
}

void init() {
    cin >> n;
    tree_init(1, n, 1);

    return;
}

void solve() {
    int m;
    int a, b, c, d;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> a;
        if (a == 1) {
            cin >> b >> c >> d;
            tree_update_range(b, c, 1, n, 1, d);
        } else {
            cin >> b;
            cout << tree_find(b, 1, n, 1) << '\n';
        }
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}