#include <algorithm>
#include <iostream>

#define N 200000
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

struct Node {
    ll lmx, rmx, sum, mx;

    Node operator+(const Node &t) const {
        Node ret;
        ret.lmx = max(lmx, sum + t.lmx);
        ret.rmx = max(t.rmx, t.sum + rmx);
        ret.sum = sum + t.sum;
        ret.mx = max({mx, t.mx, rmx + t.lmx});
        return ret;
    }
} tree[N << 2];

ll n, m, k, d;

void tree_init(int s = 1, int e = n, int i = 1) {
    tree[i].sum = (ll)(e - s + 1) * -k;
    if (s == e)
        return;
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
}

void update(int _k, int _d, int s = 1, int e = n, int i = 1) {
    if (s == e) {
        tree[i].sum += _d;
        tree[i].mx = tree[i].lmx = tree[i].rmx = max(0LL, tree[i].sum);
        return;
    }
    if (_k <= (s + e) / 2)
        update(_k, _d, s, (s + e) / 2, i << 1);
    else
        update(_k, _d, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void init() {
    cin >> n >> m >> k >> d;
    tree_init();
}

void solve() {
    int r, x;
    while (m--) {
        cin >> r >> x;
        update(r, x);
        cout << (tree[1].mx <= k * d ? "TAK\n" : "NIE\n");
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}