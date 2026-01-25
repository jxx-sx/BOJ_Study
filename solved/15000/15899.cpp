#include <algorithm>
#include <iostream>
#include <vector>
#define N 200001

using namespace std;

int in[N], out[N], tree[N];
int n, m, ord, ans, cur = 1;
pair<int, int> q[N], c[N];
vector<int> e[N];

void update(int x) {
    while (x <= n) {
        tree[x]++;
        x += x & -x;
    }
}

int sum(int x) {
    int ret = 0;
    while (x) {
        ret += tree[x];
        x -= x & -x;
    }
    return ret;
}

void dfs(int x) {
    ord++;
    in[x] = ord;
    for (auto a : e[x]) {
        if (in[a])
            continue;
        dfs(a);
    }
    out[x] = ord;
}

void init() {
    int tmp, a, b;
    cin >> n >> m >> tmp;
    for (int i = 1; i <= n; i++) {
        cin >> c[i].first;
        c[i].second = i;
    }

    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);
    }

    for (int i = 0; i < m; i++)
        cin >> q[i].second >> q[i].first;
    sort(c + 1, c + n + 1);
    sort(q, q + m);
    dfs(1);
}

void solve() {
    for (int i = 0; i < m; i++) {
        while (cur <= n) {
            if (c[cur].first > q[i].first)
                break;
            update(in[c[cur].second]);
            cur++;
        }
        ans += sum(out[q[i].second]) - sum(in[q[i].second] - 1);
        ans %= 1000000007;
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