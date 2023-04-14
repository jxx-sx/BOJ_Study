#include <iostream>

using namespace std;

long long tree[4000000];
int order[1000000];
int n, m;

void tree_init(int s, int e, int i) {
    if (s == e) {
        order[s] = i;
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
}

void tree_update(int i, int k) {
    tree[order[i]] = k;
    i = order[i] >> 1;

    while (i) {
        tree[i] = tree[i << 1] + tree[i << 1 | 1];
        i >>= 1;
    }
}

long long query(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];
    return query(l, r, s, (s + e) / 2, i << 1) + query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

void init() {
    cin >> n >> m;
    tree_init(1, n, 1);
    return;
}

void solve() {
    int a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        if (a) {
            tree_update(b, c);
        } else {
            if (b > c)
                swap(b, c);
            cout << query(b, c, 1, n, 1) << '\n';
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