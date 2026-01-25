#include <iostream>

#define N 1000000
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

int q;
pair<int, int> qry[300001];

struct Node {
    ll mx, sum;
    Node operator+(const Node &t) const {
        Node ret;
        ret.mx = max(t.mx, mx + t.sum);
        ret.sum = sum + t.sum;
        return ret;
    }
} tree[N << 2];

void update(int k, ll d, int s = 1, int e = N, int i = 1) {
    if (s == e) {
        tree[i].sum += d;
        tree[i].mx += d;
        return;
    }
    if ((s + e) / 2 < k)
        update(k, d, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        update(k, d, s, (s + e) / 2, i << 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

Node get(int l, int r, int s = 1, int e = N, int i = 1) {
    if (e < l || r < s)
        return Node();
    if (l <= s && e <= r)
        return tree[i];
    return get(l, r, s, (s + e) / 2, i << 1) + get(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
}

void init(int s = 1, int e = N, int i = 1) {
    if (s == e) {
        tree[i].mx = s;
        return;
    }
    init(s, (s + e) >> 1, i << 1);
    init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void solve() {
    cin >> q;
    char op;
    for (int i = 1; i <= q; i++) {
        auto &[a, b] = qry[i];
        cin >> op >> a;
        if (op == '+') {
            cin >> b;
            update(a, b);
        } else if (op == '-')
            update(qry[a].first, -qry[a].second);
        else
            cout << max(get(1, a).mx, (ll)a) - a << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}