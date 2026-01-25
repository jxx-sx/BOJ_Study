#include <iostream>

using namespace std;

struct Node {
    long long s, l, r, m;
    Node() : s(0), l(-10000000001), r(-10000000001), m(-10000000001) {}
};

Node tree[400000];
int arr[100001];
int n, m;

void tree_init(int s, int e, int i) {
    if (s == e) {
        tree[i].l = tree[i].r = tree[i].m = tree[i].s = arr[s];
        return;
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i].l = max(tree[i << 1].l, tree[i << 1].s + tree[i << 1 | 1].l);
    tree[i].r = max(tree[i << 1].r + tree[i << 1 | 1].s, tree[i << 1 | 1].r);
    tree[i].s = tree[i << 1].s + tree[i << 1 | 1].s;
    tree[i].m = max(max(tree[i << 1].m, tree[i << 1 | 1].m), tree[i << 1].r + tree[i << 1 | 1].l);
}

Node query(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return Node();
    if (l <= s and e <= r)
        return tree[i];

    Node ll = query(l, r, s, (s + e) / 2, i << 1);
    Node rr = query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    Node rtn;
    rtn.s = ll.s + rr.s;
    rtn.l = max(ll.l, ll.s + rr.l);
    rtn.r = max(ll.r + rr.s, rr.r);
    rtn.m = max(max(ll.m, rr.m), ll.r + rr.l);
    return rtn;
}

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    tree_init(1, n, 1);
    for (int i = 1; i <= n; i++)
        arr[i] += arr[i - 1];
    cin >> m;
}

void solve() {
    int x1, y1, x2, y2;
    while (m--) {
        Node l, m, r;
        long long ans;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x2 <= y1) {
            l = query(x1, x2 - 1, 1, n, 1);
            m = query(x2, y1, 1, n, 1);
            r = query(y1 + 1, y2, 1, n, 1);
            ans = max(max(m.m, l.r + m.s + r.l), max(l.r + m.l, m.r + r.l));
        } else {
            l = query(x1, y1 - 1, 1, n, 1);
            m = query(y1, x2, 1, n, 1);
            r = query(x2 + 1, y2, 1, n, 1);
            ans = m.s;
            ans += l.r > 0 ? l.r : 0;
            ans += r.l > 0 ? r.l : 0;
        }
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}