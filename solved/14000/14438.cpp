#include <iostream>
#define INF 1000000001

using namespace std;

int n;
int tree[400000];
int tree_data[100000];
int tree_index[100000];

int tree_init(int s, int e, int i) {
    if (s == e) {
        tree_index[s] = i;
        return tree[i] = tree_data[s];
    }
    return tree[i] = min(tree_init(s, (s + e) / 2, i << 1), tree_init((s + e) / 2 + 1, e, (i << 1) | 1));
}

void tree_update(int i, int v) {
    int cur = tree_index[i];
    tree[cur] = v;
    while ((cur >>= 1) > 0)
        tree[cur] = min(tree[cur << 1], tree[(cur << 1) | 1]);
}

int tree_find(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return INF;
    if (l <= s and e <= r)
        return tree[i];
    return min(tree_find(l, r, s, (s + e) / 2, i << 1), tree_find(l, r, (s + e) / 2 + 1, e, (i << 1) | 1));
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> tree_data[i];
    tree_init(0, n - 1, 1);
    return;
}

void solve() {
    int m;
    cin >> m;
    int a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        if (a == 1)
            tree_update(b - 1, c);
        else
            cout << tree_find(b - 1, c - 1, 0, n - 1, 1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}