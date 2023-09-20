#include <iostream>
#include <queue>
#include <vector>
#define pb push_back

using namespace std;

typedef pair<int, long> pil;

struct Node {
    int l, r;
    long long d;
    Node() : l(0), r(0), d(0) {}
} tree[202020];

int a[100000], b[100000], v[100000], comp_v[100000];
int n, m, q, ord;
vector<int> comp;

void tree_init(int s, int e, int i) {
    if (s == e)
        return;
    tree[i].l = ord++;
    tree[i].r = ord++;
    tree_init(s, (s + e) / 2, tree[i].l);
    tree_init((s + e) / 2 + 1, e, tree[i].r);
}

void update(int k, long long d, int s, int e, int cur, int before) {
    tree[cur].d = tree[before].d + d;
    if (s == e)
        return;
    if (k > (s + e) / 2) {
        tree[cur].l = tree[before].l;
        tree[cur].r = ord++;
        update(k, d, (s + e) / 2 + 1, e, tree[cur].r, tree[before].r);
    } else {
        tree[cur].l = ord++;
        tree[cur].r = tree[before].r;
        update(k, d, s, (s + e) / 2, tree[cur].l, tree[before].l);
    }
}

int query(int j, int s, int e, int l, int r) {
    if (s == e)
        return s;
    int ll = tree[tree[r].l].d - tree[tree[l].l].d;
    if (j > ll)
        return query(j - ll, (s + e) / 2 + 1, e, tree[l].r, tree[r].r);
    return query(j, s, (s + e) / 2, tree[l].l, tree[r].l);
}

void init() {
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> v[i];
        comp.pb(v[i]);
    }
    sort(comp.begin(), comp.end());
    for (int i = 0; i < m; i++)
        v[i] = lower_bound(comp.begin(), comp.end(), v[i]) - comp.begin();
    ord = m + 1;
    tree_init(0, m - 1, 0);
    for (int i = 0; i < m; i++)
        update(v[i], b[i] - a[i] + 1, 0, m - 1, i + 1, i);
}

void solve() {
    int x, y, j, l, r;
    while (q--) {
        cin >> x >> y >> j;
        cout << comp[query(j, 0, m - 1, x - 1, y)] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}