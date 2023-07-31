#include <algorithm>
#include <iostream>
#include <vector>
#define sq 1000

using namespace std;

struct Node {
    int d;
    Node *l, *r;
    Node() : d(0), l(nullptr), r(nullptr) {}
} tree[100001];
int arr[100001];
int n, m;
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
    if (s == e) {
        return;
    }
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

int query(int k, int s, int e, Node *l, Node *r) {
    if (s == e)
        return s;
    if (k > r->l->d - l->l->d)
        return query(k - (r->l->d - l->l->d), (s + e) / 2 + 1, e, l->r, r->r);
    return query(k, s, (s + e) / 2, l->l, r->l);
}

void init() {
    cin >> n >> m;
    tree_init(0, n - 1, tree);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        v.push_back(arr[i]);
    }
    sort(v.begin(), v.end());
    for (int i = 1; i <= n; i++) {
        arr[i] = lower_bound(v.begin(), v.end(), arr[i]) - v.begin();
        tree_init1(arr[i], 0, n - 1, &tree[i], &tree[i - 1]);
    }
}

void solve() {
    int l, r, k;
    for (int i = 0; i < m; i++) {
        cin >> l >> r >> k;
        cout << v[query(k, 0, n - 1, &tree[l - 1], &tree[r])] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}