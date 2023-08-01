#include <algorithm>
#include <iostream>
#include <vector>
#define N 1000001

using namespace std;

struct Node {
    int d;
    Node *l, *r;
    Node() : d(0), l(nullptr), r(nullptr) {}
    Node(Node *t) : d(t->d), l(t->l), r(t->r) {}
} tree[N];

int n, q, last;
int arr[N], pre[N];
vector<int> v;

void tree_init(int s, int e, Node *cur) {
    if (s == e)
        return;
    cur->l = new Node();
    cur->r = new Node();
    tree_init(s, (s + e) / 2, cur->l);
    tree_init((s + e) / 2 + 1, e, cur->r);
}

void tree_init1(int k, int s, int e, Node *cur, Node *before) {
    cur->d = before->d + 1;
    if (s == e)
        return;
    if (k > (s + e) / 2) {
        cur->l = before->l;
        cur->r = new Node();
        tree_init1(k, (s + e) / 2 + 1, e, cur->r, before->r);
    } else {
        cur->l = new Node();
        cur->r = before->r;
        tree_init1(k, s, (s + e) / 2, cur->l, before->l);
    }
}

void update(int k, int s, int e, Node *cur) {
    cur->d--;
    if (s == e)
        return;
    if (k > (s + e) / 2) {
        cur->r = new Node(cur->r);
        update(k, (s + e) / 2 + 1, e, cur->r);
    } else {
        cur->l = new Node(cur->l);
        update(k, s, (s + e) / 2, cur->l);
    }
}

int query(int l, int r, int s, int e, Node *cur) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return cur->d;
    return query(l, r, s, (s + e) / 2, cur->l) + query(l, r, (s + e) / 2 + 1, e, cur->r);
}

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        v.push_back(arr[i]);
    }
    cin >> q;
    sort(v.begin(), v.end());
    for (int i = 1; i <= n; i++)
        arr[i] = lower_bound(v.begin(), v.end(), arr[i]) - v.begin();

    tree_init(1, n, tree);
    for (int i = 1; i <= n; i++) {
        tree_init1(i, 1, n, tree + i, tree + i - 1);
        if (pre[arr[i]])
            update(pre[arr[i]], 1, n, tree + i);
        pre[arr[i]] = i;
    }
}

void solve() {
    int x, r;
    while (q--) {
        cin >> x >> r;
        last = query(x + last, r, 1, n, tree + r);
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