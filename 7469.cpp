#include <algorithm>
#include <iostream>
#include <vector>
#define sq 1000

using namespace std;

struct Query {
    int s, e, k, i;

    bool operator<(const Query &t) const {
        if (s / sq == t.s / sq)
            return e < t.e;
        return s < t.s;
    }
} q[5000];
int arr[100001], ans[5000], tree[400000];
int n, m, l = 1, r;
vector<int> v;

void update(int k, int d, int s, int e, int i) {
    tree[i] += d;
    if (s == k and k == e)
        return;
    if (k > (s + e) / 2)
        update(k, d, (s + e) / 2 + 1, e, i << 1 | 1);
    else
        update(k, d, s, (s + e) / 2, i << 1);
}

int query(int k, int s, int e, int i) {
    if (s == e)
        return s;

    if (tree[i << 1] < k)
        return query(k - tree[i << 1], (s + e) / 2 + 1, e, i << 1 | 1);
    return query(k, s, (s + e) / 2, i << 1);
}

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        v.push_back(arr[i]);
    }

    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e >> q[i].k;
        q[i].i = i;
    }
    sort(v.begin(), v.end());
    sort(q, q + m);
    for (int i = 1; i <= n; i++)
        arr[i] = lower_bound(v.begin(), v.end(), arr[i]) - v.begin();
}

void solve() {}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}