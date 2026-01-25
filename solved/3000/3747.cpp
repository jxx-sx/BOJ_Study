#include <iostream>
#include <stack>
#include <vector>

using namespace std;
int n, m;
int scc[2001];
vector<int> edges[2001];
vector<int> edges_r[2001];
bool is_visit[2001];
bool is_visit_r[2001];
int scc_cnt;
stack<int> st;

void dfs(int x) {
    is_visit[x] = true;
    for (auto a : edges[x])
        if (!is_visit[a])
            dfs(a);
    st.push(x);
}

void dfs_r(int x) {
    is_visit_r[x] = true;
    scc[x] = scc_cnt;
    for (auto a : edges_r[x])
        if (!is_visit_r[a])
            dfs_r(a);
}

void get_scc() {
    for (int i = 1; i < (n << 1 | 1); i++)
        if (!is_visit[i])
            dfs(i);
    while (!st.empty()) {
        if (!is_visit_r[st.top()]) {
            scc_cnt++;
            dfs_r(st.top());
        }
        st.pop();
    }
}

void init() {
    int a, b;
    scc_cnt = 0;
    for (int i = 1; i < (n << 1 | 1); i++) {
        edges[i].clear();
        edges_r[i].clear();
        is_visit_r[i] = is_visit[i] = false;
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        if (a > 0 and b > 0) {
            edges[a + n].push_back(b);
            edges[b + n].push_back(a);
            edges_r[b].push_back(a + n);
            edges_r[a].push_back(b + n);
        } else if (a < 0 and b < 0) {
            edges[-a].push_back(-b + n);
            edges[-b].push_back(-a + n);
            edges_r[-b + n].push_back(-a);
            edges_r[-a + n].push_back(-b);
        } else if (a > 0 and b < 0) {
            edges[a + n].push_back(-b + n);
            edges[-b].push_back(a);
            edges_r[-b + n].push_back(a + n);
            edges_r[a].push_back(-b);
        } else {
            edges[-a].push_back(b);
            edges[b + n].push_back(-a + n);
            edges_r[b].push_back(-a);
            edges_r[-a + n].push_back(b + n);
        }
    }

    get_scc();
    return;
}

void solve() {
    for (int i = 1; i <= n; i++)
        if (scc[i] == scc[i + n]) {
            cout << 0 << '\n';
            return;
        }
    cout << 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> n >> m) {
        init();
        solve();
    }

    return 0;
}