#include <iostream>
#include <memory.h>
#include <vector>

#define N 100001
#define pb push_back

using namespace std;

int n, m, ord, scc_cnt;
int scc[N], l[N], visited[N], in[N];
vector<int> st, e[N];

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
    for (int i = 0; i < n; i++) {
        if (visited[i])
            continue;
        dfs(i);
    }
}

void get_indegree() {
    for (int i = 0; i < n; i++) {
        for (auto a : e[i]) {
            if (scc[i] == scc[a])
                continue;
            in[scc[a]]++;
        }
    }
}

void init() {
    memset(scc, 0, sizeof(scc));
    memset(l, 0, sizeof(l));
    memset(visited, 0, sizeof(visited));
    memset(in, 0, sizeof(in));
    ord = scc_cnt = 0;

    cin >> n >> m;

    for (int i = 0; i < n; i++)
        e[i].clear();

    int a, b;
    while (m--) {
        cin >> a >> b;
        e[a].push_back(b);
    }
}

void solve() {
    tarjan();
    get_indegree();

    int ans_scc = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (in[i])
            continue;
        if (ans_scc) {
            cout << "Confused\n\n";
            return;
        }
        ans_scc = i;
    }

    for (int i = 0; i < n; i++) {
        if (scc[i] != ans_scc)
            continue;
        cout << i << '\n';
    }

    cout << '\n';
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