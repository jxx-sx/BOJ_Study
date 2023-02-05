#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> edges[20001]; // x > 0, x = x // x < 0, x = 10000 + abs(x) -> -1 == 10001, -2 == 10002
stack<int> st;
int scc[20001];
int dfs[20001];
int scc_cnt = 1, dfs_cnt = 0;
int n, m;

inline int f(int x) { return x < 0 ? 10000 - x : x; }

int find_scc(int x) {
    int ret = dfs[x] = ++dfs_cnt;
    st.push(x);
    for (auto a : edges[x]) {
        if (!dfs[a])
            ret = min(ret, find_scc(a));
        else if (!scc[a])
            ret = min(ret, dfs[a]);
    }

    if (ret == dfs[x]) {
        while (!st.empty()) {
            int cur = st.top();
            st.pop();
            scc[cur] = scc_cnt;
            if (cur == x)
                break;
        }
        scc_cnt++;
    }

    return ret;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (!dfs[i])
            find_scc(i);
        if (!dfs[10000 + i])
            find_scc(i);
    }

    for (int i = 1; i <= n; i++) {
        if (scc[i] == scc[10000 + i]) {
            cout << 0;
            return;
        }
    }
    cout << 1;
}

void init() {
    cin >> n >> m;
    int s, e;
    while (m--) {
        cin >> s >> e;
        edges[f(-s)].push_back(f(e));
        edges[f(-e)].push_back(f(s));
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}