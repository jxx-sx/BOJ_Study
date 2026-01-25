#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, ans[100001];
vector<int> v, q;

struct seg {
    int tree[400000];

    int get(int k, int s, int e, int i = 1) {
        tree[i]--;
        if (s == e)
            return s;
        if (tree[i << 1] < k)
            return get(k - tree[i << 1], (s + e) / 2 + 1, e, i << 1 | 1);
        return get(k, s, (s + e) / 2, i << 1);
    }

    void init(int s, int e, int i = 1) {
        tree[i] = e - s + 1;
        if (s == e)
            return;
        init(s, (s + e) / 2, i << 1);
        init((s + e) / 2 + 1, e, i << 1 | 1);
    }
} tree;

void init() {
    cin >> n;
    v.resize(n);
    q.resize(n);
    for (auto &a : v)
        cin >> a;
    for (auto &a : q)
        cin >> a;
    tree.init(1, n);
}

void solve() {
    sort(v.begin(), v.end());
    while (q.size()) {
        ans[q.size()] = v[tree.get(q.back() + 1, 1, n) - 1];
        q.pop_back();
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}