#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define NODE_SIZE 10975711

using namespace std;

struct Node {
    int x;
    int l, r;
    Node() : x(0), l(-1), r(-1) {}
};

struct PST {
    Node node[NODE_SIZE];
    int cnt;

    void init(int k) { cnt = k; }

    void init(int s, int e, int i = 0) {
        if (s == e)
            return;
        node[i].l = ++cnt;
        node[i].r = ++cnt;
        init(s, (s + e) / 2, node[i].l);
        init((s + e) / 2 + 1, e, node[i].r);
    }

    void init(int s, int e, int k, int before, int cur) {
        node[cur] = node[before];
        node[cur].x++;
        if (s == e)
            return;
        if ((s + e) / 2 < k) {
            node[cur].r = ++cnt;
            init((s + e) / 2 + 1, e, k, node[before].r, node[cur].r);
        } else {
            node[cur].l = ++cnt;
            init(s, (s + e) / 2, k, node[before].l, node[cur].l);
        }
    }

    int get(int s, int e, int k, int l, int r) {
        if (s == e)
            return s;
        int l_cnt = node[node[r].l].x - node[node[l].l].x;
        if (l_cnt < k)
            return get((s + e) / 2 + 1, e, k - l_cnt, node[l].r, node[r].r);
        return get(s, (s + e) / 2, k, node[l].l, node[r].l);
    }
} pst;

int n;
long long ans;
vector<int> v, ind;
queue<pair<int, int>> q;

void quick_sort_cnt(int l, int r) {
    if (r - l <= 1)
        return;
    ans += r - l;
    int cur = (pst.node[r].x - pst.node[l].x - 1) >> 1;
    int pivot = v[pst.get(0, n - 1, cur + 1, l, r)];
    q.push({l, pivot - 1});
    q.push({pivot, r});
}

void init() {
    cin >> n;
    v.resize(n);
    ind.resize(n + 1);

    for (auto &a : v)
        cin >> a;
    for (int i = 0; i < n; i++)
        ind[v[i]] = i;

    pst.init(n);
    pst.init(0, n - 1);
    for (int i = 1; i <= n; i++)
        pst.init(0, n - 1, ind[i], i - 1, i);
}

void solve() {
    q.push({0, n});
    while (q.size()) {
        quick_sort_cnt(q.front().first, q.front().second);
        q.pop();
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}