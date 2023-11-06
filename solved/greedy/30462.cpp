#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n;
vector<int> v;
int tree[800000];
int ans[200001];

void tree_init(int s, int e, int i) {
    tree[i] = e - s + 1;
    if (s == e)
        return;
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
}

int get(int k, int s, int e, int i) {
    if (k <= s)
        return tree[i];
    if (e < k)
        return 0;
    return get(k, s, (s + e) / 2, i << 1) + get(k, (s + e) / 2 + 1, e, i << 1 | 1);
}

void update(int k, int s, int e, int i) {
    tree[i]--;
    if (s == e)
        return;
    if ((s + e) / 2 < k)
        update(k, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        update(k, s, (s + e) / 2, i << 1);
}

bool peek(int k, int s, int e, int i) {
    if (s == e)
        return tree[i];

    if ((s + e) / 2 < k)
        return peek(k, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        return peek(k, s, (s + e) / 2, i << 1);
}

bool peek(int l, int r, int s, int e, int i) {
    if (l <= s and e <= r)
        return tree[i];
    if (e < l or r < s)
        return false;

    return peek(l, r, (s + e) / 2 + 1, e, i << 1 | 1) | peek(l, r, s, (s + e) / 2, i << 1);
}

int get(int s, int e, int i) {
    if (s == e)
        return s;
    if (tree[i << 1 | 1])
        return get((s + e) / 2 + 1, e, i << 1 | 1);
    else
        return get(s, (s + e) / 2, i << 1);
}

void init() {
    cin >> n;
    v.resize(n);
    for (auto &a : v)
        cin >> a;
    tree_init(1, n, 1);
}

void solve() {
    if (v.back() != n + 1) {
        cout << "No";
        return;
    }
    int cur = n + 1;
    v.pop_back();
    while (v.size()) {
        if (v.size() + 1 < v.back()) {
            cout << "No";
            return;
        }
        if (v.back() > cur) {
            cout << "No";
            return;
        }
        if (v.back() == cur) {
            int tmp = get(1, n, 1);
            if (tmp <= v.back()) {
                cout << "No";
                return;
            }
            ans[v.size()] = tmp;
            update(tmp, 1, n, 1);
        }
        if (v.back() < cur) {
            if (!peek(v.back(), 1, n, 1)) {
                cout << "No";
                return;
            }
            ans[v.size()] = v.back();
            update(v.back(), 1, n, 1);
            cur = v.back();
        }
        v.pop_back();
    }
    ans[0] = get(1, n, 1);
    if (ans[0] == cur) {
        cout << "No";
        return;
    }
    cout << "Yes\n";
    for (int i = 0; i < n; i++)
        cout << ans[i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}