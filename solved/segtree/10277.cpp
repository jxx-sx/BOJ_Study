#include <iostream>
#include <string>

using namespace std;

struct Node {
    int d, mx, mn;
} tree[18350080];
int c, n, o;

void push(int x) {
    if (!tree[x].d)
        return;
    tree[x << 1].d += tree[x].d;
    tree[x << 1].mx += tree[x].d;
    tree[x << 1].mn += tree[x].d;
    tree[x << 1 | 1].d += tree[x].d;
    tree[x << 1 | 1].mx += tree[x].d;
    tree[x << 1 | 1].mn += tree[x].d;
    tree[x].d = 0;
}

void update(int l, int r, int d, int s, int e, int i) {
    if (e < l or r < s)
        return;
    if (l <= s and e <= r) {
        tree[i].d += d;
        tree[i].mx += d;
        tree[i].mn += d;
        return;
    }
    push(i);
    update(l, r, d, s, (s + e) / 2, i << 1);
    update(l, r, d, (s + e) / 2 + 1, e, i << 1 | 1);
    tree[i].mx = max(tree[i << 1].mx, tree[i << 1 | 1].mx);
    tree[i].mn = min(tree[i << 1].mn, tree[i << 1 | 1].mn);
}

int get_mx(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i].mx;
    push(i);
    return max(get_mx(l, r, s, (s + e) / 2, i << 1), get_mx(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
}

int get_mn(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return n + 1;
    if (l <= s and e <= r)
        return tree[i].mn;
    push(i);
    return min(get_mn(l, r, s, (s + e) / 2, i << 1), get_mn(l, r, (s + e) / 2 + 1, e, i << 1 | 1));
}

int query(int x, int s, int e, int i) {
    if (s == x and x == e)
        return tree[i].d;
    push(i);
    if (x > (s + e) / 2)
        return query(x, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        return query(x, s, (s + e) / 2, i << 1);
}

void init() { cin >> c >> n >> o; }

void solve() {
    int a, b, s;
    string op;
    while (o--) {
        cin >> op;
        if (op == "change") {
            cin >> a >> s;
            if (s > 0) {
                auto tmp = get_mx(a, a, 0, c - 1, 1);
                s = s + tmp > n ? n - tmp : s;
            } else {
                auto tmp = get_mn(a, a, 0, c - 1, 1);
                s = s + tmp < 0 ? -tmp : s;
            }
            update(a, a, s, 0, c - 1, 1);
            cout << s << '\n';
        }
        if (op == "groupchange") {
            cin >> a >> b >> s;
            if (s > 0) {
                auto tmp = get_mx(a, b, 0, c - 1, 1);
                s = s + tmp > n ? n - tmp : s;
            } else {
                auto tmp = get_mn(a, b, 0, c - 1, 1);
                s = s + tmp < 0 ? -tmp : s;
            }
            update(a, b, s, 0, c - 1, 1);
            cout << s << '\n';
        }
        if (op == "state") {
            cin >> a;
            cout << query(a, 0, c - 1, 1) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}