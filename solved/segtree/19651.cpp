#include <algorithm>
#include <iostream>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n, m;

struct Arr {
    long long v, lz_a1, lz_d;
} arr[400000];

void push(int s, int e, int i) {
    if (!(arr[i].lz_a1 | arr[i].lz_d))
        return;

    arr[i << 1].v += arr[i].lz_a1;
    arr[i << 1 | 1].v += arr[i].lz_a1 + arr[i].lz_d * ((s + e) / 2 + 1 - s);

    arr[i << 1].lz_a1 += arr[i].lz_a1;
    arr[i << 1 | 1].lz_a1 += arr[i].lz_a1 + arr[i].lz_d * ((s + e) / 2 + 1 - s);

    arr[i << 1].lz_d += arr[i].lz_d;
    arr[i << 1 | 1].lz_d += arr[i].lz_d;

    arr[i].lz_a1 = arr[i].lz_d = 0;
}

void arr_init(int s = 1, int e = n, int i = 1) {
    if (s == e) {
        cin >> arr[i].v;
        return;
    }
    arr_init(s, (s + e) / 2, i << 1);
    arr_init((s + e) / 2 + 1, e, i << 1 | 1);
}

void add(int l, int r, long long a1, long long d, int s = 1, int e = n, int i = 1) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        arr[i].v += a1 + d * (s - l);
        arr[i].lz_a1 += a1 + d * (s - l);
        arr[i].lz_d += d;
        return;
    }
    push(s, e, i);
    add(l, r, a1, d, s, (s + e) / 2, i << 1);
    add(l, r, a1, d, (s + e) / 2 + 1, e, i << 1 | 1);
}

long long get(int k, int s = 1, int e = n, int i = 1) {
    if (s == e)
        return arr[i].v;
    push(s, e, i);
    if (k > (s + e) / 2)
        return get(k, (s + e) / 2 + 1, e, i << 1 | 1);
    return get(k, s, (s + e) / 2, i << 1);
}

struct Seg {
    int lmx, rmx, mx, sum;
    bool valid;

    Seg(long long x = 0, bool valid = true) : lmx(x ? 0 : 1), rmx(x ? 0 : 1), mx(x ? 0 : 1), sum(1), valid(valid) {}
    Seg(int lmx, int rmx, int mx, int sum) : lmx(lmx), rmx(rmx), mx(mx), sum(sum), valid(true) {}
    Seg operator+(const Seg &t) const {
        return Seg(lmx == sum ? sum + t.lmx : lmx, t.rmx == t.sum ? rmx + t.sum : t.rmx, max({mx, t.mx, rmx + t.lmx}), sum + t.sum);
    }
} tree[400000];

void update(int k, long long x, int s = 1, int e = n, int i = 1) {
    if (s == e) {
        tree[i] = Seg(x);
        return;
    }
    if (k > (s + e) / 2)
        update(k, x, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        update(k, x, s, (s + e) / 2, i << 1);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

Seg query(int l, int r, int s = 1, int e = n, int i = 1) {
    if (e < l or r < s)
        return Seg(1, false);
    if (l <= s and e <= r)
        return tree[i];
    Seg ll = query(l, r, s, (s + e) / 2, i << 1);
    Seg rr = query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    if (!ll.valid)
        return rr;
    if (!rr.valid)
        return ll;
    return ll + rr;
}

void init() {
    cin >> n;
    arr_init();
    for (int i = 2; i < n; i++)
        update(i, get(i - 1) + get(i + 1) - (get(i) << 1));
    update(1, -1);
    update(n, -1);
    cin >> m;
}

void solve() {
    int op, i, j;
    long long x, y;
    while (m--) {
        cin >> op >> i >> j;
        if (op == 1) {
            cin >> x >> y;
            add(i, j, x, y);
            for (auto a : {i - 1, i, j, j + 1})
                if (1 < a and a < n)
                    update(a, get(a - 1) + get(a + 1) - (get(a) << 1));
        } else
            cout << (j - i == 1 ? 2 : query(i + 1, j - 1).mx + 2) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}