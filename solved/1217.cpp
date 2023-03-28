#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int n, m;
vector<int> edges[40001];
vector<int> edges_r[40001];
bool is_visit[40001];
bool is_visit_r[40001];
int scc[40001];
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
    for (int i = 1; i < (m << 1 | 1); i++)
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

bool init() {
    cin >> n >> m;
    scc_cnt = 0;
    if (n == 0 and m == 0)
        return false;
    int a, b, na, nb;
    for (int i = 1; i < (m << 1 | 1); i++) {
        edges[i].clear();
        edges_r[i].clear();
        is_visit[i] = is_visit_r[i] = false;
    }

    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        if (a < 0) {
            na = -a;
            a = -a + m;
        } else
            na = a + m;
        if (b < 0) {
            nb = -b;
            b = -b + m;
        } else
            nb = b + m;
        edges[a].push_back(nb);
        edges[b].push_back(na);
        edges_r[nb].push_back(a);
        edges_r[na].push_back(b);
    }

    get_scc();
    return true;
}

void solve() {
    for (int i = 1; i <= m; i++)
        if (scc[i] == scc[i + m]) {
            cout << 0 << '\n';
            return;
        }
    cout << 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (init())
        solve();

    return 0;
}