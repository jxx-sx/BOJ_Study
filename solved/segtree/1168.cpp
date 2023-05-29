#include <iostream>

using namespace std;

int tree[400000];
int n, k, cur;

int tree_init(int s, int e, int i) {
    if (s == e)
        return tree[i] = 1;
    return tree[i] = tree_init(s, (s + e) / 2, i << 1) + tree_init((s + e) / 2 + 1, e, i << 1 | 1);
}

int query(int f, int s, int e, int i) {
    tree[i]--;
    if (s == e)
        return s;

    if (tree[i << 1] < f) {
        f -= tree[i << 1];
        return query(f, (s + e) / 2 + 1, e, i << 1 | 1);
    } else
        return query(f, s, (s + e) / 2, i << 1);
}

void init() {
    cin >> n >> k;
    tree_init(1, n, 1);
}

void solve() {
    cur = k;
    k -= 2;
    cout << '<' << query(cur, 1, n, 1);
    while (tree[1]) {
        cur += k;
        cur %= tree[1];
        cur++;
        cout << ", " << query(cur, 1, n, 1);
    }
    cout << '>';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}