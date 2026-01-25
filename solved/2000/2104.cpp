#include <algorithm>
#include <iostream>

using namespace std;

pair<long long, int> tree[400000]; // sum, min_i
long long arr[100000];
int n;
long long ans = 0;

pair<long long, int> tree_init(int s, int e, int i) {
    if (s == e) {
        tree[i].first = arr[s];
        tree[i].second = s;
        return tree[i];
    }
    tree_init(s, (s + e) / 2, i << 1);
    tree_init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i].first = tree[i << 1].first + tree[i << 1 | 1].first;
    tree[i].second = arr[tree[i << 1].second] < arr[tree[i << 1 | 1].second] ? tree[i << 1].second : tree[i << 1 | 1].second;
    return tree[i];
}

pair<long long, int> query(int l, int r, int s, int e, int i) {
    if (e < l or r < s)
        return {0, -1};
    if (l <= s and e <= r)
        return tree[i];
    pair<long long, int> ll, rr, rtn;
    ll = query(l, r, s, (s + e) / 2, i << 1);
    rr = query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    rtn.first = ll.first + rr.first;
    if (ll.second != -1 and rr.second != -1)
        rtn.second = arr[ll.second] < arr[rr.second] ? ll.second : rr.second;
    else if (ll.second == -1)
        rtn.second = rr.second;
    else
        rtn.second = ll.second;
    return rtn;
}

void recursion(int l, int r) {
    if (r < l)
        return;
    pair<long long, int> q = query(l, r, 0, n - 1, 1);
    ans = max(ans, q.first * arr[q.second]);
    recursion(l, q.second - 1);
    recursion(q.second + 1, r);
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    tree_init(0, n - 1, 1);
    return;
}

void solve() {
    recursion(0, n - 1);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}