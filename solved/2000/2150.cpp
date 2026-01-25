#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

stack<int> st;
vector<int> v[10001];
vector<int> v_r[10001];
vector<vector<int>> ans;
bool check[10001];
bool check_r[10001];
int V, E;

bool cmp(vector<int> a, vector<int> b) { return a.front() < b.front(); }

void dfs(int x) {
    check[x] = true;
    for (auto i : v[x]) {
        if (!check[i])
            dfs(i);
    }
    st.push(x);

    return;
}

void dfs_r(int x, int ind) {
    check_r[x] = true;
    ans[ind].push_back(x);
    for (auto i : v_r[x]) {
        if (!check_r[i])
            dfs_r(i, ind);
    }

    return;
}

void solve() {
    while (!st.empty()) {
        if (!check_r[st.top()]) {
            ans.push_back(vector<int>());
            dfs_r(st.top(), ans.size() - 1);
        }
        st.pop();
    }

    for (int i = 0; i < ans.size(); i++)
        sort(ans[i].begin(), ans[i].end());
    sort(ans.begin(), ans.end(), cmp);

    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++)
            cout << ans[i][j] << ' ';
        cout << "-1\n";
    }

    return;
}

void init() {
    cin >> V >> E;
    for (int i = 0; i <= V; i++) {
        check[i] = check_r[i] = false;
    }
    int s, e;
    for (int i = 0; i < E; i++) {
        cin >> s >> e;
        v[s].push_back(e);
        v_r[e].push_back(s);
    }

    for (int i = 1; i <= V; i++)
        if (!check[i])
            dfs(i);

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}