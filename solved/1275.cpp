#include <iostream>

using namespace std;

int n, q;
long long tree[400000];
long long tree_data[100001];
int tree_index[100001];

long long tree_init(int s, int e, int i) {
    if (s == e) {
        tree_index[s] = i;
        return tree[i] = tree_data[s];
    }
    return tree[i] = tree_init(s, (s + e) / 2, i * 2) + tree_init((s + e) / 2 + 1, e, i * 2 + 1);
}

void tree_update(int a, int b) {
    int cur = tree_index[a];
    tree[cur] = b;
    while ((cur >> 1) > 0) {
        cur >>= 1;
        tree[cur] = tree[cur << 1] + tree[(cur << 1) | 1];
    }
}

long long tree_find(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];
    return tree_find(l, r, s, (s + e) / 2, i << 1) + tree_find(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

void init() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> tree_data[i];
    tree_init(1, n, 1);
    return;
}

void solve() {
    int x, y, a, b;
    for (int i = 0; i < q; i++) {
        cin >> x >> y >> a >> b;
        if (x > y)
            swap(x, y);
        cout << tree_find(x, y, 1, n, 1) << '\n';
        tree_update(a, b);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}