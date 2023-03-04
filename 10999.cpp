#include <iostream>
#define MAX_SIZE 1000000

using namespace std;

long long tree[4 * MAX_SIZE];
long long lazy[4 * MAX_SIZE];
int n, m, k;
long long tree_init(int s, int e, int i) {
    if (s == e) {
        cin >> tree[i];
        return tree[i];
    }
    return tree[i] = tree_init(s, (s + e) / 2, i << 1) + tree_init((s + e) / 2 + 1, e, (i << 1) | 1);
}

void lazy_update(int s, int e, int i) {
    if (lazy[i] == 0)
        return;
    if (e - s) {
        tree[i] += lazy[i] * (e - s + 1);
        lazy[i << 1] = lazy[(i << 1) | 1] = lazy[i];
    } else
        tree[i] += lazy[i];
    lazy[i] = 0;
}

int get_range(int l, int r, int s, int e) {
    if (l <= s and e <= r)
        return e - s + 1;
    if (e < r)
        return e - l + 1;
    return r - s + 1;
}

void tree_update_range(int l, int r, int s, int e, int i, long long diff) {
    if (e < l or r < s)
        return;
    lazy_update(s, e, i);
    int range = get_range(l, r, s, e);
    if (range == e - s + 1) {
        if (range != 1) { // !leaf
            tree[i] += diff * range;
            lazy[i << 1] += diff;
            lazy[(i << 1) | 1] += diff;
        } else // leaf
            tree[i] += diff;
        return;
    }
    tree[i] += diff * range;
    tree_update_range(l, r, s, (s + e) / 2, i << 1, diff);
    tree_update_range(l, r, (s + e) / 2 + 1, e, (i << 1) | 1, diff);
}

long long tree_find(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return 0;
    lazy_update(s, e, i);
    if (l <= s and e <= r)
        return tree[i];
    return tree_find(l, r, s, (s + e) / 2, i << 1) + tree_find(l, r, (s + e) / 2 + 1, e, (i << 1) | 1);
}

void init() {
    cin >> n >> m >> k;
    tree_init(1, n, 1);
    return;
}

void solve() {
    int a, b, c, d;
    for (int i = 0; i < m + k; i++) {
        cin >> a;
        if (a == 1) {
            cin >> b >> c >> d;
            tree_update_range(b, c, 1, n, 1, d);
        } else {
            cin >> b >> c;
            cout << tree_find(b, c, 1, n, 1) << '\n';
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