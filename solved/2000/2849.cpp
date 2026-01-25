#include <algorithm>
#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#define L 0
#define R 1

using namespace std;

struct Seg {
    int lmx, rmx, mx, sum, s, e;
    Seg(int x = 1) : lmx(x), rmx(x), mx(x), sum(x), s(L), e(L) {}
    Seg(int lmx, int rmx, int mx, int sum, int s, int e) : lmx(lmx), rmx(rmx), mx(mx), sum(sum), s(s), e(e) {}
    Seg operator+(const Seg &t) const {
        return Seg(mx == sum and e ^ t.s ? sum + t.lmx : lmx, t.mx == t.sum and e ^ t.s ? rmx + t.sum : t.rmx, max({mx, t.mx, e ^ t.s ? rmx + t.lmx : 0}),
                   sum + t.sum, s, t.e);
    }
} tree[800000];

void init(int s, int e, int i = 1) {
    if (s == e)
        return;
    tree[i].sum = e - s + 1;
    init(s, (s + e) / 2, i << 1);
    init((s + e) / 2 + 1, e, i << 1 | 1);
}

void update(int k, int s, int e, int i = 1) {
    if (s == e) {
        tree[i].s ^= 1;
        tree[i].e ^= 1;
        return;
    }
    if (k > (s + e) / 2)
        update(k, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        update(k, s, (s + e) / 2, i << 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

int n, q;

void init() {
    cin >> n >> q;
    init(1, n);
}

void solve() {
    int k;
    while (q--) {
        cin >> k;
        update(k, 1, n);
        cout << tree[1].mx << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}