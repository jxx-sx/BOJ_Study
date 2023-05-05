#include <iostream>

using namespace std;

long long tree[4000000];
int n, q;

void tree_update(int p, int k, int s, int e, int i) {
    tree[i] += k;
    if (s == p and e == p)
        return;
    if (s <= p and p <= (s + e) / 2)
        tree_update(p, k, s, (s + e) / 2, i << 1);
    else
        tree_update(p, k, (s + e) / 2 + 1, e, i << 1 | 1);
}

long long query(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];
    return query(l, r, s, (s + e) / 2, i << 1) + query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

void init() {
    cin >> n >> q;
    return;
}

void solve() {
    int a, b, c;
    for (int i = 0; i < q; i++) {
        cin >> a >> b >> c;
        if (a == 1)
            tree_update(b, c, 1, n, 1);
        else
            cout << query(b, c, 1, n, 1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}