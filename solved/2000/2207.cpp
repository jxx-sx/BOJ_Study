#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> edges[20001]; // 1~n = 양수 그대로, n+1 ~ 2n = 음수 변환
vector<int> edges_r[20001];
stack<int> st;
int scc[20001];
int scc_cnt;
int n, m;
bool is_visit[20001];
bool is_visit_r[20001];

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

void init() {
    int x, y, not_x, not_y;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        if (x < 0) {
            not_x = -x;
            x = -x + m;
        } else
            not_x = x + m;

        if (y < 0) {
            not_y = -y;
            y = -y + m;
        } else
            not_y = y + m;

        edges[not_x].push_back(y);
        edges_r[y].push_back(not_x);

        edges[not_y].push_back(x);
        edges_r[x].push_back(not_y);
    }
    return;
}

void get_scc() {
    for (int i = 1; i <= 2 * n; i++)
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

void solve() {
    get_scc();
    for (int i = 1; i <= m; i++)
        if (scc[i] == scc[i + m]) {
            cout << "OTL";
            return;
        }
    cout << "^_^";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}