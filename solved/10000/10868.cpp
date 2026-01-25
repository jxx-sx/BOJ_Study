#include <iostream>
#define INF 1000000001

using namespace std;

int n, m;
int tree_data[100000];
int tree[400000];

int tree_init(int s, int e, int i) {
    if (s == e)
        return tree[i] = tree_data[s];
    return tree[i] = min(tree_init(s, (s + e) / 2, i * 2), tree_init((s + e) / 2 + 1, e, i * 2 + 1));
}

int tree_find(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return INF;
    if (l <= s and e <= r)
        return tree[i];
    return min(tree_find(l, r, s, (s + e) / 2, i * 2), tree_find(l, r, (s + e) / 2 + 1, e, i * 2 + 1));
}

void init() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> tree_data[i];
    tree_init(0, n - 1, 1);
    return;
}

void solve() {
    int s, e;
    for (int i = 0; i < m; i++) {
        cin >> s >> e;
        cout << tree_find(s - 1, e - 1, 0, n - 1, 1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
    return 0;
}