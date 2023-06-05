#include <iostream>

using namespace std;

pair<int, int> tree[400000];
int n;

void tree_init(int s, int e, int i) {
    if (s == e) {
        cin >> tree[i].first;
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1].first > tree[i << 1 | 1].first ? make_pair(tree[i << 1].first, max(tree[i << 1].second, tree[i << 1 | 1].first))
                                                          : make_pair(tree[i << 1 | 1].first, max(tree[i << 1].first, tree[i << 1 | 1].second));
}

void update(int k, int v, int s, int e, int i) {
    if (s == e) {
        tree[i].first = v;
        return;
    }
    if ((s + e) / 2 < k)
        update(k, v, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        update(k, v, s, (s + e) / 2, i << 1);
    tree[i] = tree[i << 1].first > tree[i << 1 | 1].first ? make_pair(tree[i << 1].first, max(tree[i << 1].second, tree[i << 1 | 1].first))
                                                          : make_pair(tree[i << 1 | 1].first, max(tree[i << 1].first, tree[i << 1 | 1].second));
}

pair<int, int> query(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return {0, 0};
    if (l <= s and e <= r)
        return tree[i];

    pair<int, int> ll, rr;
    ll = query(l, r, s, (s + e) / 2, i << 1);
    rr = query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    return ll.first > rr.first ? make_pair(ll.first, max(ll.second, rr.first)) : make_pair(rr.first, max(ll.first, rr.second));
}

void init() {
    cin >> n;
    tree_init(1, n, 1);
}

void solve() {
    int m, q, a, b;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q >> a >> b;
        if (q == 1)
            update(a, b, 1, n, 1);
        else {
            pair<int, int> ans = query(a, b, 1, n, 1);
            cout << ans.first + ans.second << '\n';
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