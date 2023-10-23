#include <iostream>
#include <vector>

#define N 10001
#define pb push_back

using namespace std;

int n, m, s, t, ord, scc_ord, visited[N], scc[N], scc_cnt[N], l[N], dp[N];
vector<int> scc_e[N], e[N], st;

int dfs(int x) {
    visited[x] = l[x] = ++ord;
    st.pb(x);

    for (auto a : e[x]) {
        if (!visited[a])
            l[x] = min(l[x], dfs(a));
        else if (!scc[a])
            l[x] = min(l[x], l[a]);
    }

    if (l[x] == visited[x]) {
        scc_ord++;
        while (true) {
            scc[st.back()] = scc_ord;
            scc_cnt[scc_ord]++;
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
    for (int i = 1; i <= n; i++)
        if (!visited[i])
            dfs(i);
}

void init() {
    int a, b;
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        e[a].pb(b);
    }
}

void solve() {
    tarjan();
    s = scc[s];
    t = scc[t];
    dp[s] = scc_cnt[s];
    for (int i = 1; i <= n; i++)
        for (auto a : e[i]) {
            if (scc[i] == scc[a])
                continue;
            scc_e[scc[i]].pb(scc[a]);
        }

    for (int i = s; i > t; i--) {
        if (!dp[i])
            continue;
        for (auto a : scc_e[i])
            dp[a] = max(dp[a], dp[i] + scc_cnt[a]);
    }
    cout << dp[t];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}