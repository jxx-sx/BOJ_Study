#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<int> edges[20001]; // Ai = i, -Ai = i + n
vector<int> scc(20001, -1);
vector<int> dfs(20001, -1);
stack<int> st;
int scc_cnt = 0, dfs_cnt = 0;
int n, m;

int find_scc(int x) {
    int ret = dfs[x] = dfs_cnt++;
    st.push(x);
    for (auto a : edges[x]) {
        if (dfs[a] == -1)
            ret = min(ret, find_scc(a));
        else if (scc[a] == -1)
            ret = min(ret, dfs[a]);
    }
    if (ret == dfs[x]) {
        while (!st.empty()) {
            int cur = st.top();
            st.pop();
            scc[cur] = scc_cnt;
            if (cur == ret)
                break;
        }
        scc_cnt++;
    }

    return ret;
}

void solve() {
    for (int i = 1; i <= n; i++)
        if (dfs[i] == -1)
            find_scc(i);
    for (int i = 1; i <= n; i++) {
        if (scc[i] == scc[i + n]) {
            cout << 0;
            return;
        }
    }
    cout << 1;
}

void init() {
    cin >> n >> m;
    int s, e, not_s, not_e;
    for (int i = 0; i < m; i++) {
        cin >> s >> e;
        if (s < 0) {
            not_s = -s;
            s = -s + n;
        } else {
            not_s = s + n;
        }
        if (e < 0) {
            not_e = -e;
            e = -e + n;
        } else {
            not_e = e + n;
        }
        edges[not_s].push_back(e);
        edges[not_e].push_back(s);
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