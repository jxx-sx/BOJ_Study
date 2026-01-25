#include <iostream>
#define INF 1000000001

using namespace std;

int n;
pair<int, int> tree[400000];
int tree_data[100000];
int tree_index[100000];

pair<int, int> tree_init(int s, int e, int i) {
    if (s == e) {
        tree_index[s] = i;
        return tree[i] = {tree_data[s], s + 1};
    }
    pair<int, int> l = tree_init(s, (s + e) / 2, i << 1);
    pair<int, int> r = tree_init((s + e) / 2 + 1, e, (i << 1) | 1);
    return tree[i] = (r.first < l.first ? r : l);
}

void tree_update(int i, int x) {
    int cur = tree_index[i];
    tree[cur].first = x;

    while ((cur >>= 1) > 0)
        tree[cur] = (tree[(cur << 1) | 1].first < tree[cur << 1].first ? tree[(cur << 1) | 1] : tree[cur << 1]);
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
        cin >> a;
        if (a == 1) {
            cin >> b >> c;
            tree_update(b - 1, c);
        } else
            cout << tree[1].second << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}