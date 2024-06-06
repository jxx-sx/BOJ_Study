#include <iostream>
#include <vector>

#define N 303
#define R 0
#define INF 1001001001001
#define pb push_back
#define eb emplace_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

struct Edge {
    int s, e, w;
    Edge(int s, int e, int w) : s(s), e(e), w(w) {}
};
int n, prv[N], lbl[N];
ll x[N], mn[N], mn_w[N];
vector<Edge> e;

ll dmst() {
    int _n = n + 1, k;
    ll ret = 0;
    int r = 0;
    while (true) {
        for (int i = 0; i < N; i++) {
            mn_w[i] = INF;
            lbl[i] = -1;
        }
        for (auto [u, v, w] : e) {
            if (u != v && w < mn_w[v]) {
                prv[v] = u;
                mn_w[v] = w;
            }
        }
        mn_w[r] = 0;
        for (int i = 0; i < _n; i++)
            ret += mn_w[i];
        k = 1;
        lbl[r] = 0;
        for (int i = 0; i < _n; i++) {
            if (lbl[i] == -1) {
                int j = i;
                for (; lbl[j] == -1; j = prv[j])
                    lbl[j] = -2;
                if (lbl[j] == -2) {
                    for (; lbl[j] == -2; j = prv[j])
                        lbl[j] = k;
                    k++;
                }
                for (j = i; lbl[j] == -2; j = prv[j])
                    lbl[j] = k++;
            }
        }
        if (_n == k)
            break;
        _n = k;
        for (auto &[u, v, w] : e) {
            w -= mn_w[v];
            u = lbl[u];
            v = lbl[v];
        }
    }
    return ret;
}

void init() {
    ll w;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    for (int i = 1; i <= n; i++) {
        cin >> mn[i];
        e.eb(R, i, mn[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> w;
            e.eb(i, j, w);
            mn[j] = min(w, mn[j]);
        }
    }
}

void solve() {
    ll ans = dmst();
    for (int i = 1; i <= n; i++)
        ans += mn[i] * (x[i] - 1);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}