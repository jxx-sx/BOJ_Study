#include <iostream>

using namespace std;

pair<long long, long long> tree[400000];
int n;

void push_down(int i, int d) {
    if (tree[i].first) {
        tree[i << 1].first += tree[i].first;
        tree[i << 1].second += tree[i].second;
        tree[i << 1 | 1].first += tree[i].first + tree[i].second * d;
        tree[i << 1 | 1].second += tree[i].second;
        tree[i] = {0, 0};
    }
}

void tree_init(int s, int e, int i) {
    if (s == e) {
        cin >> tree[i].first;
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
}

void update(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i].first += s - l + 1;
        tree[i].second += 1;
        return;
    }

    update(l, r, s, (s + e) / 2, i << 1);
    update(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

long long query(int x, int s, int e, int i) {
    if (s == e)
        return tree[i].first;
    push_down(i, (s + e) / 2 + 1 - s);
    if ((s + e) / 2 < x)
        return query(x, (s + e) / 2 + 1, e, i << 1 | 1);
    return query(x, s, (s + e) / 2, i << 1);
}

void init() {
    cin >> n;
    tree_init(1, n, 1);
    return;
}

void solve() {
    int m, q, l, r;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q >> l;
        if (q == 1) {
            cin >> r;
            update(l, r, 1, n, 1);
        } else
            cout << query(l, 1, n, 1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
    
    return 0;
}