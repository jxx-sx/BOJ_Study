#include <iostream>
#define MAX_SIZE 1000000

using namespace std;

long long tree[4 * MAX_SIZE];
long long lazy[4 * MAX_SIZE];
long long tree_data[MAX_SIZE + 1];
int n, m, k;
long long tree_init(int s, int e, int i) {
    if (s == e)
        return (tree[i] = tree_data[s]);
    return tree[i] = tree_init(s, (s + e) / 2, i << 1) + tree_init((s + e) / 2 + 1, e, (i << 1) | 1);
}

void propagate(int s, int e, int i) {
    if (lazy[i] == 0)
        return;

    if (s != e) { // not leaf
        lazy[i << 1] += lazy[i];
        lazy[(i << 1) | 1] += lazy[i];
    }
    tree[i] += lazy[i] * (e - s + 1);
    lazy[i] = 0;
}

int get_range(int l, int r, int s, int e) {
    if (e < l or r < s)
        return 0;
    return min(r, e) - max(l, s) + 1;
}

void tree_update_range(int l, int r, int s, int e, int i, long long diff) {
    propagate(s, e, i);
    if (e < l or r < s)
        return;
    int range = get_range(l, r, s, e);
    if (l <= s and e <= r) {
        if (s != e) { // !leaf
            lazy[i << 1] += diff;
            lazy[(i << 1) | 1] += diff;
        }
        tree[i] += diff * range;
        return;
    }
    tree_update_range(l, r, s, (s + e) / 2, i << 1, diff);
    tree_update_range(l, r, (s + e) / 2 + 1, e, (i << 1) | 1, diff);
    tree[i] = tree[i << 1] + tree[(i << 1) | 1];
}

long long tree_find(int l, int r, int s, int e, int i) {
    propagate(s, e, i);
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];
    return tree_find(l, r, s, (s + e) / 2, i << 1) + tree_find(l, r, (s + e) / 2 + 1, e, (i << 1) | 1);
}

void init() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        cin >> tree_data[i];
    tree_init(1, n, 1);
    return;
}

void solve() {
    int a, b, c;
    long long d;
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