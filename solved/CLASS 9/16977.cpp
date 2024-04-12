#include <algorithm>
#include <iostream>
#include <vector>

#define N 100001
#define pb push_back
#define li (i << 1)
#define ri (i << 1 | 1)

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

struct Node {
    int sum, lmx, rmx, mx;
    Node(int x = 0) : sum(x), lmx(x), rmx(x), mx(x) {}
    Node(int sum, int lmx, int rmx, int mx) : sum(sum), lmx(lmx), rmx(rmx), mx(mx) {}
    Node operator+(const Node &t) const {
        return Node(sum + t.sum, lmx + (lmx == sum ? t.lmx : 0), t.rmx + (t.rmx == t.sum ? rmx : 0), max({mx, t.mx, rmx + t.lmx}));
    }
} tree[N << 2];

int n, q;
int arr[N], ans[N];
int l[N], r[N];
vector<int> m[N], comp, ind[N];
bool flag;
struct Query {
    int l, r, w;
} qry[N];

Node query(int l, int r, int s = 1, int e = n, int i = 1) {
    if (e < l or r < s)
        return Node();
    if (l <= s and e <= r)
        return tree[i];
    return query(l, r, s, (s + e) >> 1, li) + query(l, r, ((s + e) >> 1) + 1, e, ri);
}

inline int get(int l, int r) { return query(l, r).mx; }

void update(int k, int s = 1, int e = n, int i = 1) {
    if (s == e) {
        tree[i].lmx = tree[i].rmx = tree[i].mx = 0;
        return;
    }
    if ((s + e) >> 1 < k)
        update(k, ((s + e) >> 1) + 1, e, ri);
    else
        update(k, s, (s + e) >> 1, li);
    tree[i] = tree[li] + tree[ri];
}

void init(int s, int e, int i = 1) {
    tree[i] = Node(e - s + 1);
    if (s == e) {
        return;
    }
    init(s, (s + e) >> 1, li);
    init(((s + e) >> 1) + 1, e, ri);
}

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        comp.pb(arr[i]);
    }
    sort(comp.begin(), comp.end());
    for (int i = 1; i <= n; i++)
        ind[lower_bound(comp.begin(), comp.end(), arr[i]) - comp.begin()].pb(i);
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> qry[i].l >> qry[i].r >> qry[i].w;
        r[i] = n - 1;
    }
}

inline void clear() {
    init(1, n);
    for (int i = 0; i < N; i++)
        m[i].clear();
}

void solve() {
    while (true) {
        flag = true;
        clear();
        for (int i = 0; i < q; i++) {
            if (l[i] <= r[i]) {
                m[(l[i] + r[i]) >> 1].push_back(i);
                flag = false;
            }
        }
        if (flag)
            break;
        for (int i = 0; i < n; i++) {
            for (auto a : m[i]) {
                if (get(qry[a].l, qry[a].r) >= qry[a].w) {
                    l[a] = i + 1;
                    ans[a] = comp[i];
                } else {
                    r[a] = i - 1;
                }
            }
            for (auto a : ind[i])
                update(a);
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