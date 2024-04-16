#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#define N 100001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

int n, m, q, cur;
int arr[N], l[N], r[N], ans[N];
bool flag;
vector<int> v, mi[N];

struct Qry {
    int a, b, v;
    bool operator<(const Qry &t) const { return v < t.v; }
} qry[N];

struct Proc {
    int x, y;
    ll j;
} proc[N];

struct Seg {
    ll v, sz, lz;
} tree[N << 4];

inline void push(int i) {
    if (!tree[i].lz)
        return;
    for (auto a : {i << 1, i << 1 | 1}) {
        tree[a].v += tree[i].lz * tree[a].sz;
        tree[a].lz += tree[i].lz;
    }
    tree[i].lz = 0;
}

void update(int l, int r, int s = 0, int e = v.size() - 2, int i = 1) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i].v += tree[i].sz;
        tree[i].lz++;
        return;
    }
    push(i);
    update(l, r, s, (s + e) >> 1, i << 1);
    update(l, r, ((s + e) >> 1) + 1, e, i << 1 | 1);
    tree[i].v = tree[i << 1].v + tree[i << 1 | 1].v;
}

ll get(int l, int r, int s = 0, int e = v.size() - 2, int i = 1) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i].v;
    push(i);
    return get(l, r, s, (s + e) >> 1, i << 1) + get(l, r, ((s + e) >> 1) + 1, e, i << 1 | 1);
}

void tree_init(int s = 0, int e = v.size() - 2, int i = 1) {
    tree[i].v = tree[i].lz = 0;
    if (s == e)
        return;
    tree_init(s, (s + e) >> 1, i << 1);
    tree_init(((s + e) >> 1) + 1, e, i << 1 | 1);
}

void init(int s, int e = v.size() - 2, int i = 1) {
    tree[i].sz = v[e + 1] - v[s];
    if (s == e)
        return;
    init(s, (s + e) >> 1, i << 1);
    init(((s + e) >> 1) + 1, e, i << 1 | 1);
}

void init() {
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        cin >> qry[i].a >> qry[i].b >> qry[i].v;
        qry[i].b++;
        v.pb(qry[i].a);
        v.pb(qry[i].b);
    }
    sort(qry, qry + m);
    for (int i = 0; i < q; i++) {
        cin >> proc[i].x >> proc[i].y >> proc[i].j;
        proc[i].y++;
        v.pb(proc[i].x);
        v.pb(proc[i].y);
        r[i] = m - 1;
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 0; i < m; i++) {
        qry[i].a = lower_bound(v.begin(), v.end(), qry[i].a) - v.begin();
        qry[i].b = lower_bound(v.begin(), v.end(), qry[i].b) - v.begin();
    }

    for (int i = 0; i < q; i++) {
        proc[i].x = lower_bound(v.begin(), v.end(), proc[i].x) - v.begin();
        proc[i].y = lower_bound(v.begin(), v.end(), proc[i].y) - v.begin();
    }
    init(0);
}

void solve() {
    while (true) {
        for (int i = 0; i < m; i++)
            mi[i].clear();
        tree_init();
        flag = true;
        for (int i = 0; i < q; i++) {
            if (l[i] <= r[i]) {
                mi[(l[i] + r[i]) >> 1].pb(i);
                flag = false;
            }
        }
        if (flag)
            break;
        for (int i = 0; i < m; i++) {
            update(qry[i].a, qry[i].b - 1);
            for (auto a : mi[i]) {
                if (get(proc[a].x, proc[a].y - 1) >= proc[a].j) {
                    ans[a] = qry[i].v;
                    r[a] = i - 1;
                } else
                    l[a] = i + 1;
            }
        }
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}