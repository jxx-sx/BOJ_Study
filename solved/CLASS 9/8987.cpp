#include <iostream>
#include <queue>
#include <vector>

#define N 150000
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

struct Node {
    int s, e, h;
} node[N];

vector<pair<int, int>> v;
int tree[N << 2];
int n, k;
ll ans;
priority_queue<ll> pq;

void init(int s, int e, int i = 1) {
    if (s == e) {
        tree[i] = s;
        return;
    }
    init(s, (s + e) / 2, i << 1);
    init((s + e) / 2 + 1, e, i << 1 | 1);
    tree[i] = node[tree[i << 1]].h < node[tree[i << 1 | 1]].h ? tree[i << 1] : tree[i << 1 | 1];
}

int query(int l, int r, int s = 1, int e = n - 1, int i = 1) {
    if (e < l or r < s)
        return 0;
    if (l <= s and e <= r)
        return tree[i];
    int ll = query(l, r, s, (s + e) / 2, i << 1);
    int rr = query(l, r, (s + e) / 2 + 1, e, i << 1 | 1);
    return node[ll].h < node[rr].h ? ll : rr;
}

ll dnc(int s = 1, int e = n - 1, int prev = 0) {
    if (e < s)
        return 0;
    int i = query(s, e);
    int h = node[i].h;

    ll l = dnc(s, i - 1, h);
    ll r = dnc(i + 1, e, h);

    pq.push(min(l, r));
    return max(l, r) + ll(node[e].e - node[s].s) * (h - prev);
}

void init() {
    pair<int, int> _;
    cin >> n;
    cin >> _.first >> _.second;
    n >>= 1;
    node[0].h = 2e9;
    for (int i = 1; i < n; i++)
        cin >> node[i].s >> node[i].h >> node[i].e >> node[i].h;
    cin >> _.first >> _.second >> k;
    init(1, n - 1);
}

void solve() {
    pq.push(dnc());
    while (k-- && !pq.empty()) {
        ans += pq.top();
        pq.pop();
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