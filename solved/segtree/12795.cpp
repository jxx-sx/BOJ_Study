#include <iostream>
#include <vector>

#define N 1'000'000'000'000LL
#define INF 2'000'000'000'000'000'001LL
#define eb emplace_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

struct Line {
    ll a, b;
    ll get(ll x) { return a * x + b; }
    Line(ll a = 0, ll b = -INF) : a(a), b(b) {}
};

struct Node {
    int l, r;
    Line line;
    Node(ll a = 0, ll b = -INF) : l(-1), r(-1), line(a, b) {}
    Node(Line line) : l(-1), r(-1), line(line) {}
};

int q;
vector<Node> tree;

void update(Line line, ll s = -N, ll e = N, int i = 0) {
    Line lo = tree[i].line, hi = line;
    if (lo.get(s) > hi.get(s))
        swap(lo, hi);
    if (lo.get(e) <= hi.get(e)) {
        tree[i].line = hi;
        return;
    }
    if (s == e)
        return;

    ll m = (s + e) / 2;
    if (lo.get(m) < hi.get(m)) {
        tree[i].line = hi;
        if (tree[i].r == -1) {
            tree[i].r = tree.size();
            tree.eb();
        }
        update(lo, m + 1, e, tree[i].r);
    } else {
        tree[i].line = lo;
        if (tree[i].l == -1) {
            tree[i].l = tree.size();
            tree.eb();
        }
        update(hi, s, m, tree[i].l);
    }
}

ll qry(ll x, ll s = -N, ll e = N, int i = 0) {
    if (i == -1)
        return -INF;
    if (x > (s + e) / 2)
        return max(tree[i].line.get(x), qry(x, (s + e) / 2 + 1, e, tree[i].r));
    return max(tree[i].line.get(x), qry(x, s, (s + e) / 2, tree[i].l));
}

void init() {
    tree.eb();
    cin >> q;
}

void solve() {
    int op;
    ll a, b;
    while (q--) {
        cin >> op >> a;
        if (op == 1) {
            cin >> b;
            update(Line(a, b));
        } else
            cout << qry(a) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}