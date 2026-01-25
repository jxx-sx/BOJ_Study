#include <iostream>
#include <vector>

#define N 100001
#define pb push_back

using namespace std;

int n, s, ans;
int ord, scc_cnt;
int visited[N], l[N], scc[N], scc_sum[N], dp[N];
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

    if (visited[x] == l[x]) {
        scc_cnt++;
        while (true) {
            scc[st.back()] = scc_cnt;
            scc_sum[scc_cnt]++;
            if (x == st.back()) {
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
    int a;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        if (i - a > 0)
            e[i].pb(i - a);
        if (i + a <= n)
            e[i].pb(i + a);
    }
    cin >> s;
}

void solve() {
    tarjan();
    for (int i = 1; i <= n; i++) {
        for (auto a : e[i]) {
            if (scc[i] == scc[a])
                continue;
            scc_e[scc[i]].pb(scc[a]);
        }
    }

    s = scc[s];
    dp[s] = scc_sum[s];
    ans = dp[s];

    for (int i = s; i > 0; i--) {
        if (!dp[i])
            continue;
        for (auto a : scc_e[i]) {
            dp[a] = max(dp[a], dp[i] + scc_sum[a]);
            ans = max(ans, dp[a]);
        }
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