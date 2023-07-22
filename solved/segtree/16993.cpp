#include <iostream>

using namespace std;

struct Node {
    int a, l, r, m;
    Node() : a(0), l(-1010101010), r(-1010101010), m(-1010101010) {}
};

Node tree[400004];
int arr[100001];
int n;

void tree_init(int s, int e, int i) {
    if (s == e) {
        tree[i].l = tree[i].r = tree[i].m = tree[i].a = arr[s];
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i].a = tree[i << 1].a + tree[i << 1 | 1].a;
    tree[i].l = max(tree[i << 1].l, tree[i << 1].a + tree[i << 1 | 1].l);
    tree[i].r = max(tree[i << 1 | 1].r, tree[i << 1].r + tree[i << 1 | 1].a);
    tree[i].m = max(max(tree[i << 1].m, tree[i << 1 | 1].m), tree[i << 1].r + tree[i << 1 | 1].l);
}

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    tree_init(1, n, 1);

    return;
}

Node query(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return Node();
    if (l <= s and e <= r)
        return tree[i];
    Node rtn, ll, rr;
    ll = query(l, r, s, (s + e) / 2, i << 1);
    rr = query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    rtn.a = ll.a + rr.a;
    rtn.l = max(ll.l, ll.a + rr.l);
    rtn.r = max(rr.r, rr.a + ll.r);
    rtn.m = max(max(ll.m, rr.m), ll.r + rr.l);
    return rtn;
}

void solve() {
    int q, l, r;
    cin >> q;
    while (q--) {
        cin >> l >> r;
        cout << query(l, r, 1, n, 1).m << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}