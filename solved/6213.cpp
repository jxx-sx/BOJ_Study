#include <iostream>

using namespace std;

int min_tree[200000];
int max_tree[200000];
int tree_data[50000];
int n, m;

int min_tree_init(int s, int e, int i) {
    if (s == e)
        return min_tree[i] = tree_data[s - 1];
    return min_tree[i] = min(min_tree_init(s, (s + e) / 2, i << 1), min_tree_init((s + e) / 2 + 1, e, i << 1 | 1));
}

int max_tree_init(int s, int e, int i) {
    if (s == e)
        return max_tree[i] = tree_data[s - 1];
    return max_tree[i] = max(max_tree_init(s, (s + e) / 2, i << 1), max_tree_init((s + e) / 2 + 1, e, i << 1 | 1));
}

int find_min(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return 1000001;
    if (l <= s and e <= r)
        return min_tree[i];
    return min(find_min(l, r, s, (s + e) / 2, i << 1), find_min(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
}

int find_max(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return max_tree[i];
    return max(find_max(l, r, s, (s + e) / 2, i << 1), find_max(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> tree_data[i];

    min_tree_init(1, n, 1);
    max_tree_init(1, n, 1);

    return;
}

void solve() {
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        cout << find_max(a, b, 1, n, 1) - find_min(a, b, 1, n, 1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}