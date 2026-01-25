#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#define N 100001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

int n, k, j, cur, p;
int in[N], out[N], l[N], r[N];
ll tree[N];
struct Qry {
    int t, p, s;
    bool operator<(const Qry &t) const { return this->t < t.t; }
} qry[N];
vector<int> e[N], songs[N], m[N];
int singer[N];
int ans[N];
bool flag;

void dfs(int x = 1) {
    in[x] = ++cur;
    for (auto a : e[x]) {
        if (in[a])
            continue;
        dfs(a);
    }
    out[x] = cur;
}

void update(int x, int d) {
    int st = in[x];
    while (st <= n) {
        tree[st] += d;
        st += st & -st;
    }

    int ed = out[x] + 1;
    while (ed <= n) {
        tree[ed] -= d;
        ed += ed & -ed;
    }
}

bool check(int x) {
    ll ret = 0;
    for (auto a : songs[x]) {
        int i = in[a];
        while (i) {
            ret += tree[i];
            i -= i & -i;
        }
        if (ret > (ll)j * songs[x].size())
            return true;
    }
    return false;
}

void init() {
    cin >> n >> k >> j;
    for (int i = 2; i <= n; i++) {
        cin >> p;
        e[p].pb(i);
    }
    for (int i = 1; i <= n; i++) {
        cin >> singer[i];
        ans[singer[i]] = -1;
        songs[singer[i]].pb(i);
    }
    dfs();

    for (int i = 0; i < k; i++) {
        cin >> qry[i].t >> qry[i].p >> qry[i].s;
        qry[i].s /= out[qry[i].p] - in[qry[i].p] + 1;
    }
    sort(qry, qry + k);
    for (int i = 1; i <= n; i++)
        r[i] = songs[i].size() ? k - 1 : -1;
}

void solve() {
    while (true) {
        flag = true;
        for (int i = 0; i < k; i++)
            m[i].clear();
        for (int i = 1; i <= n; i++)
            tree[i] = 0;
        for (int i = 1; i <= n; i++) {
            if (l[i] <= r[i]) {
                m[(l[i] + r[i]) >> 1].pb(i);
                flag = false;
            }
        }
        if (flag)
            break;
        for (int i = 0; i < k; i++) {
            update(qry[i].p, qry[i].s);
            for (auto a : m[i]) {
                if (check(a)) {
                    ans[a] = qry[i].t;
                    r[a] = i - 1;
                } else 
                    l[a] = i + 1;
            }
        }
    }
    for (int i = 1; i <= n; i++)
        cout << ans[singer[i]] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}