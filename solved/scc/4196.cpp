#include <iostream>
#include <vector>

using namespace std;

int n, m, scc_cnt, dfs_ord;
int in_degree[100001], ord[100001], l[100001], scc[100001];
vector<int> v[100001], st;

int dfs(int x) {
    ord[x] = l[x] = ++dfs_ord;
    st.push_back(x);
    for (auto a : v[x]) {
        if (!ord[a])
            l[x] = min(l[x], dfs(a));
        else if (!scc[a])
            l[x] = min(l[x], l[a]);
        else
            in_degree[scc[a]]++;
    }

    if (ord[x] == l[x]) {
        scc_cnt++;
        while (true) {
            scc[st.back()] = scc_cnt;
            if (st.back() == x) {
                st.pop_back();
                break;
            }
            st.pop_back();
        }
        if (st.size())
            in_degree[scc_cnt]++;
    }
    return l[x];
}

void tarjan() {
    for (int i = 1; i <= n; i++)
        if (!ord[i])
            dfs(i);
}

void init() {
    cin >> n >> m;
    scc_cnt = dfs_ord = 0;
    for (int i = 1; i <= n; i++) {
        ord[i] = l[i] = scc[i] = in_degree[i] = 0;
        v[i].clear();
    }
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        v[a].push_back(b);
    }
}

void solve() {
    tarjan();
    int ans = 0;
    for (int i = 1; i <= scc_cnt; i++)
        if (!in_degree[i])
            ans++;
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    while (tc--) {
        init();
        solve();
    }

    return 0;
}