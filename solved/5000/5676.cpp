#include <iostream>

using namespace std;

int n, k;
int tree[400000];
int leaf[100001];

int tree_init(int s, int e, int i) {
    if (s == e) {
        cin >> tree[i];
        if (tree[i] != 0)
            tree[i] = tree[i] > 0 ? 1 : -1;
        leaf[s] = i;
        return tree[i];
    }
    return tree[i] = tree_init(s, (s + e) / 2, i << 1) * tree_init((s + e) / 2 + 1, e, i << 1 | 1);
}

void tree_update(int i, int x) {
    if (x != 0)
        x = x > 0 ? 1 : -1;
    tree[leaf[i]] = x;
    int cur = leaf[i] >> 1;
    while (cur) {
        tree[cur] = tree[cur << 1] * tree[cur << 1 | 1];
        cur >>= 1;
    }
}

int tree_find(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return 1;
    if (l <= s and e <= r)
        return tree[i];
    return tree_find(l, r, s, (s + e) / 2, i << 1) * tree_find(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

void init() {
    tree_init(1, n, 1);

    return;
}

void solve() {
    char q;
    int x, v;

    for (int i = 0; i < k; i++) {
        cin >> q >> x >> v;
        if (q == 'C')
            tree_update(x, v);
        else {
            int ans = tree_find(x, v, 1, n, 1);
            if (ans != 0)
                cout << (ans > 0 ? '+' : '-');
            else
                cout << 0;
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> n >> k) {
        init();
        solve();
    }

    return 0;
}