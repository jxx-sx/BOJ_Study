#include <iostream>

using namespace std;

long long tree[4000000];
long long lazy[4000000];
int n, m;

void propagate(int s, int e, int x) {
    if (lazy[x]) {
        tree[x] += (long long)(e - s + 1) * lazy[x];
        if (s != e) {
            lazy[x << 1] += lazy[x];
            lazy[x << 1 | 1] += lazy[x];
        }
        lazy[x] = 0;
    }
}

long long tree_init(int s, int e, int i) {
    if (s == e) {
        cin >> tree[i];
        return tree[i];
    }
    return tree[i] = tree_init(s, (s + e) / 2, i << 1) + tree_init((s + e) / 2 + 1, e, i << 1 | 1);
}

long long query(int l, int r, int s, int e, int i) {
    propagate(s, e, i);
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];
    return query(l, r, s, (s + e) / 2, i << 1) + query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

void update(int l, int r, int k, int s, int e, int i) {
    propagate(s, e, i);
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        lazy[i] += k;
        propagate(s, e, i);
        return;
    }
    update(l, r, k, s, (s + e) / 2, i << 1);
    update(l, r, k, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void init() {
    int q;
    cin >> n >> m >> q;
    m += q;
    tree_init(1, n, 1);
}

void solve() {
    int q, a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> q >> a >> b;
        if (q == 1)
            cout << query(a, b, 1, n, 1) << '\n';
        else {
            cin >> c;
            update(a, b, c, 1, n, 1);
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