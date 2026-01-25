#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int n;
vector<int> edges[100001];
stack<int> cur_vertex;
int connected_vertex_cnt[100001];

void init() {
    cin >> n;
    int s, e;
    for (int i = 0; i < n - 1; i++) {
        cin >> s >> e;
        edges[s].push_back(e);
        edges[e].push_back(s);
    }

    for (int i = 1; i <= n; i++) {
        sort(edges[i].begin(), edges[i].end());
        connected_vertex_cnt[i] = edges[i].size();
    }

    return;
}

void solve() {
    int dfs;
    cin >> dfs;
    cur_vertex.push(1);
    for (auto a : edges[1])
        connected_vertex_cnt[a]--;

    for (int i = 1; i < n; i++) {
        cin >> dfs;
        if (!binary_search(edges[cur_vertex.top()].begin(), edges[cur_vertex.top()].end(), dfs)) {
            cout << 0;
            return;
        }

        cur_vertex.push(dfs);
        for (auto a : edges[dfs])
            connected_vertex_cnt[a]--;

        while (!cur_vertex.empty())
            if (connected_vertex_cnt[cur_vertex.top()] == 0)
                cur_vertex.pop();
            else
                break;
    }
    cout << 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();

    return 0;
}
