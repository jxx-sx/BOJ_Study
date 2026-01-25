#include <algorithm>
#include <iostream>
#include <vector>

#define N 500001
#define pb push_back

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

int n;
vector<int> v, e[N];
vector<pair<int, int>> arr;
bool visited[N];
int v_cnt, e_cnt, mx;
long long ans, sum;

void dfs(int x) {
    mx = max(v[x], mx);
    sum += v[x];
    v_cnt++;
    e_cnt += e[x].size();
    visited[x] = true;
    for (auto a : e[x]) {
        if (visited[a])
            continue;
        dfs(a);
    }
}

void init() {
    cin >> n;
    arr.resize(n);
    for (auto &[a, b] : arr) {
        cin >> a >> b;
        v.pb(a), v.pb(b);
        ans += a + b;
    }
    sort(v.begin(), v.end());
    for (auto [a, b] : arr) {
        a = lower_bound(v.begin(), v.end(), a) - v.begin();
        b = lower_bound(v.begin(), v.end(), b) - v.begin();
        e[a].pb(b);
        e[b].pb(a);
    }
}

void solve() {
    for (int i = 0; i < (n << 1); i++) {
        if (visited[i])
            continue;
        sum = mx = v_cnt = e_cnt = 0;
        dfs(i);
        ans -= sum;
        if ((e_cnt >> 1) != v_cnt)
            ans += mx;
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