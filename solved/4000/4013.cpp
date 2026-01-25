#include <iostream>
#include <vector>

#define N 500001
#define pb push_back

using namespace std;

int n, m, s, p, ans, ord, scc_cnt, dp[N], money[N], visited[N], scc[N], l[N], money_sum[N];
vector<int> scc_e[N], e[N], p_arr, st;

int dfs(int x) {
    visited[x] = l[x] = ++ord;
    st.pb(x);
    for (auto a : e[x]) {
        if (!visited[a])
            l[x] = min(l[x], dfs(a));
        else if (!scc[a])
            l[x] = min(l[x], l[a]);
    }
    if (visited[x] == l[x]) {
        scc_cnt++;
        while (true) {
            scc[st.back()] = scc_cnt;
            money_sum[scc[st.back()]] += money[st.back()];
            if (st.back() == x) {
                st.pop_back();
                break;
            }
            st.pop_back();
        }
    }
    return l[x];
}

void tarjan() {
    for (int i = 1; i <= n; i++) {
        if (visited[i])
            continue;
        dfs(i);
    }
}

void init() {
    int a, b;
    cin >> n >> m;
    while (m--) {
        cin >> a >> b;
        e[a].pb(b);
    }
    for (int i = 1; i <= n; i++)
        cin >> money[i];
    cin >> s >> p;
    p_arr.resize(p);
    for (auto &a : p_arr)
        cin >> a;
}

void solve() {
    tarjan();
    for (int i = 1; i <= n; i++)
        for (auto a : e[i]) {
            if (scc[i] == scc[a])
                continue;
            scc_e[scc[i]].pb(scc[a]);
        }
    s = scc[s];
    dp[s] = money_sum[s];

    for (int i = s; i > 0; i--) {
        if (!dp[i])
            continue;
        for (auto a : scc_e[i])
            dp[a] = max(dp[a], dp[i] + money_sum[a]);
    }

    for (auto a : p_arr)
        ans = max(ans, dp[scc[a]]);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}