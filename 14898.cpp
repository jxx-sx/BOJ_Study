#include <algorithm>
#include <iostream>
#include <vector>
#define pb push_back
#define N 1000001
#define NN                                                                                                                                                     \
    tree.size();                                                                                                                                               \
    tree.pb(Node())

using namespace std;

struct Node {
    int d, l, r;
    Node() : d(0), l(0), r(0) {}
    void copy(Node *t) {
        d = t->d;
        l = t->l;
        r = t->r;
    }
};

int n, q, last;
int arr[N], pre[N], comp[N];
vector<Node> tree;

void tree_init(int s, int e, int cur) {
    if (s == e)
        return;
    tree[cur].l = NN;
    tree[cur].r = NN;
    tree_init(s, (s + e) / 2, tree[cur].l);
    tree_init((s + e) / 2 + 1, e, tree[cur].r);
}

void tree_init1(int k, int s, int e, int cur, int before) {
    tree[cur].d = tree[before].d + 1;
    if (s == e)
        return;
    if (k > (s + e) / 2) {
        tree[cur].l = tree[before].l;
        tree[cur].r = NN;
        tree_init1(k, (s + e) / 2 + 1, e, tree[cur].r, tree[before].r);
    } else {
        tree[cur].l = NN;
        tree[cur].r = tree[before].r;
        tree_init1(k, s, (s + e) / 2, tree[cur].l, tree[before].l);
    }
}

void update(int k, int s, int e, int cur) {
    tree[cur].d--;
    if (s == e)
        return;
    if (k > (s + e) / 2) {
        Node *tmp = &tree[tree[cur].r];
        tree[cur].r = NN;
        tree[tree[cur].r].copy(tmp);
        update(k, (s + e) / 2 + 1, e, tree[cur].r);
    } else {
        Node *tmp = &tree[tree[cur].l];
        tree[cur].l = NN;
        tree[tree[cur].l].copy(tmp);
        update(k, s, (s + e) / 2, tree[cur].l);
    }
}

int query(int l, int r, int s, int e, int cur) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[cur].d;
    return query(l, r, s, (s + e) / 2, tree[cur].l) + query(l, r, (s + e) / 2 + 1, e, tree[cur].r);
}

void init() {
    cin >> n;
    tree.pb(Node());
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        comp[i] = arr[i];
        tree.pb(Node());
    }
    cin >> q;
    sort(comp, comp + n);
    for (int i = 0; i < n; i++)
        arr[i] = lower_bound(comp, comp + n, arr[i]) - comp;

    tree_init(1, n, 0);
    for (int i = 0; i < n; i++) {
        tree_init1(i + 1, 1, n, i + 1, i);
        if (pre[arr[i]])
            update(pre[arr[i]], 1, n, i + 1);
        pre[arr[i]] = i + 1;
    }
}

void solve() {
    int x, r;
    while (q--) {
        cin >> x >> r;
        last = query(x + last, r, 1, n, r);
        cout << last << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}