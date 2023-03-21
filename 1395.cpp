#include <iostream>

using namespace std;

int tree[400000];
bool lazy[400000];
int n, m;

inline int get_range(int l, int r, int s, int e) { return min(r, e) - max(l, s) + 1; }

void propagate(int s, int e, int x) {
    if (lazy[x]) {
        lazy[x << 1] = !lazy[x << 1];
        lazy[x << 1 | 1] = !lazy[x << 1 | 1];
        tree[x] = e - s + 1 - tree[x];
        lazy[x] = false;
    }
}

int find_tree(int l, int r, int s, int e, int i) {
    propagate(s, e, i);
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];

    return find_tree(l, r, s, (s + e) / 2, i << 1) + find_tree(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

int update(int l, int r, int s, int e, int i) {
    propagate(s, e, i);
    if (e < l or r < s)
        return tree[i];

    if (l <= s and e <= r) {
        if (s != e) {
            lazy[i << 1] = !lazy[i << 1];
            lazy[i << 1 | 1] = !lazy[i << 1 | 1];
        }
        return tree[i] = e - s + 1 - tree[i];
    }

    return tree[i] = update(l, r, s, (s + e) / 2, i << 1) + update(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

void init() {
    cin >> n >> m;
    return;
}

void solve() {
    int mode, a, b;
    for (int i = 0; i < m; i++) {
        cin >> mode >> a >> b;
        if (mode)
            cout << find_tree(a, b, 1, n, 1) << '\n';
        else
            update(a, b, 1, n, 1);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
